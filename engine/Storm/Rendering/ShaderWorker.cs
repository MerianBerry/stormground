namespace Storm.Core;
using System.Threading;

public class ShaderWorker {
  public struct Input {
    public string name;
    public string code;
  }

  private IntPtr                session;
  private volatile Queue<Input> queue;
  private Mutex                 mut;

  private IntPtr result;
  private int    resultInd;

  private int submitted;

  private bool run;

  public ShaderWorker() {
    queue     = [];
    mut       = new();
    run       = true;
    submitted = 0;
    resultInd = -1;
  }

  public int Start (in SRP srp) {
    mut.WaitOne();
    /*session = Native.Storm_CreateShaderSession (srp.format);
    if (session == 0)
      throw new Exception ("Workerhandle is null");*/
    mut.ReleaseMutex();
    while (run) {
      mut.WaitOne();
      if (queue.Count() > 0) {
        Input shader = queue.Dequeue();
        mut.ReleaseMutex();
        /*IntPtr r =
          Native.Storm_CompileShader (session, shader.name, shader.code);*/
        IntPtr r = 0;
        mut.WaitOne();
        Console.WriteLine ("Done compiling shader " + shader.name);
        result = r;
        resultInd++;
        mut.ReleaseMutex();
      } else {
        mut.ReleaseMutex();
      }
      Thread.Sleep (10);
    }
    return 0;
  }

  public void Stop() {
    run = false;
  }

  public IntPtr[] SubmitWork (in Input[] shaders) {
    IntPtr[] results = new IntPtr[shaders.Length];
    mut.WaitOne();
    int index = submitted;
    foreach (Input code in shaders) {
      queue.Enqueue (code);
      submitted++;
    }
    mut.ReleaseMutex();
    for (int i = 0; i < shaders.Length; i++) {
      while (resultInd != index + i) {
        Thread.Sleep (10);
      }
      mut.WaitOne();
      results[i] = result;
      mut.ReleaseMutex();
    }
    Console.WriteLine ("Im done working :)");
    return results;
  }

  public Task<IntPtr[]> SubmitWorkAsync (Input[] shaders) => Task.Run (
    () => this.SubmitWork (shaders));
}