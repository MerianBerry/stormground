
namespace Storm.Core;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices.Marshalling;
using SDL3;

public static partial class Native {
  [CustomMarshaller (typeof (string), MarshalMode.ManagedToUnmanagedOut,
    typeof (CallerOwnedStringMarshaller))]
  public static unsafe class CallerOwnedStringMarshaller {
    /// <summary>
    /// Converts an unmanaged string to a managed version.
    /// </summary>
    /// <returns>A managed string.</returns>
    public static string ConvertToManaged (
      byte* unmanaged) => Marshal.PtrToStringUTF8 ((IntPtr)unmanaged);

    /// <summary>
    /// Free the memory for a specified unmanaged string.
    /// </summary>
    public static void Free (byte* unmanaged) => Storm_Free ((IntPtr)unmanaged);
  }

  public readonly record struct StormBool {
    private readonly byte value;

    internal const byte FALSE_VALUE = 0;
    internal const byte TRUE_VALUE  = 1;

    internal StormBool (byte value) {
      this.value = value;
    }

    public static implicit operator bool (StormBool b) {
      return b.value != FALSE_VALUE;
    }

    public static implicit operator StormBool (bool b) {
      return new StormBool (b ? TRUE_VALUE : FALSE_VALUE);
    }

    public bool Equals (StormBool other) {
      return other.value == value;
    }

    public override int GetHashCode() {
      return value.GetHashCode();
    }
  }

  private const string lib = "NativeStorm";

  [LibraryImport (lib)]
  public static partial void Storm_Free (IntPtr ptr);


  [LibraryImport (lib, StringMarshalling = StringMarshalling.Utf8)]
  public static partial void Storm_SetError (string msg);

  [LibraryImport (lib, StringMarshalling = StringMarshalling.Utf8)]
  [return:MarshalUsing (typeof (CallerOwnedStringMarshaller))]
  public static partial string Storm_GetError();


  [LibraryImport (lib, StringMarshalling = StringMarshalling.Utf8)]
  public static partial void Storm_LogInfo (string source, string? msg,
    string? trace);

  [LibraryImport (lib, StringMarshalling = StringMarshalling.Utf8)]
  public static partial void Storm_LogWarn (string source, string? msg,
    string? trace);

  [LibraryImport (lib, StringMarshalling = StringMarshalling.Utf8)]
  public static partial void Storm_LogError (string source, string? msg,
    string? trace = null);

  /*[LibraryImport (lib)]
  public static partial IntPtr Storm_CreateShaderSession (
    SDL.SDL_GPUShaderFormat format);

  [LibraryImport (lib, StringMarshalling = StringMarshalling.Utf8)]
  public static partial IntPtr Storm_CompileShader (IntPtr session, string name,
    string code);*/
}