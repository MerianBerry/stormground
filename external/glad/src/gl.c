/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/gl.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif




static GLADapiproc glad_gl_internal_loader_get_proc(const char *name);
static GLADloadfunc glad_global_on_demand_gl_loader_func = glad_gl_internal_loader_get_proc;

void gladSetGLOnDemandLoader(GLADloadfunc loader) {
    glad_global_on_demand_gl_loader_func = loader;
}

static GLADapiproc glad_gl_on_demand_loader(const char *name) {
    GLADapiproc result = NULL;
    if (result == NULL && glad_global_on_demand_gl_loader_func != NULL) {
        result = glad_global_on_demand_gl_loader_func(name);
    }
    /* this provokes a segmentation fault if there was no loader or no loader returned something useful */
    return result;
}


static void GLAD_API_PTR glad_on_demand_impl_glActiveTexture(GLenum texture) {
    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC) glad_gl_on_demand_loader("glActiveTexture");
    glad_glActiveTexture(texture);
}
PFNGLACTIVETEXTUREPROC glad_glActiveTexture = glad_on_demand_impl_glActiveTexture;
static void GLAD_API_PTR glad_on_demand_impl_glActiveTextureARB(GLenum texture) {
    glad_glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) glad_gl_on_demand_loader("glActiveTextureARB");
    glad_glActiveTextureARB(texture);
}
PFNGLACTIVETEXTUREARBPROC glad_glActiveTextureARB = glad_on_demand_impl_glActiveTextureARB;
static void GLAD_API_PTR glad_on_demand_impl_glActiveVaryingNV(GLuint program, const GLchar * name) {
    glad_glActiveVaryingNV = (PFNGLACTIVEVARYINGNVPROC) glad_gl_on_demand_loader("glActiveVaryingNV");
    glad_glActiveVaryingNV(program, name);
}
PFNGLACTIVEVARYINGNVPROC glad_glActiveVaryingNV = glad_on_demand_impl_glActiveVaryingNV;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glAreProgramsResidentNV(GLsizei n, const GLuint * programs, GLboolean * residences) {
    glad_glAreProgramsResidentNV = (PFNGLAREPROGRAMSRESIDENTNVPROC) glad_gl_on_demand_loader("glAreProgramsResidentNV");
    return glad_glAreProgramsResidentNV(n, programs, residences);
}
PFNGLAREPROGRAMSRESIDENTNVPROC glad_glAreProgramsResidentNV = glad_on_demand_impl_glAreProgramsResidentNV;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glAreTexturesResidentEXT(GLsizei n, const GLuint * textures, GLboolean * residences) {
    glad_glAreTexturesResidentEXT = (PFNGLARETEXTURESRESIDENTEXTPROC) glad_gl_on_demand_loader("glAreTexturesResidentEXT");
    return glad_glAreTexturesResidentEXT(n, textures, residences);
}
PFNGLARETEXTURESRESIDENTEXTPROC glad_glAreTexturesResidentEXT = glad_on_demand_impl_glAreTexturesResidentEXT;
static void GLAD_API_PTR glad_on_demand_impl_glArrayElementEXT(GLint i) {
    glad_glArrayElementEXT = (PFNGLARRAYELEMENTEXTPROC) glad_gl_on_demand_loader("glArrayElementEXT");
    glad_glArrayElementEXT(i);
}
PFNGLARRAYELEMENTEXTPROC glad_glArrayElementEXT = glad_on_demand_impl_glArrayElementEXT;
static void GLAD_API_PTR glad_on_demand_impl_glAttachObjectARB(GLhandleARB containerObj, GLhandleARB obj) {
    glad_glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) glad_gl_on_demand_loader("glAttachObjectARB");
    glad_glAttachObjectARB(containerObj, obj);
}
PFNGLATTACHOBJECTARBPROC glad_glAttachObjectARB = glad_on_demand_impl_glAttachObjectARB;
static void GLAD_API_PTR glad_on_demand_impl_glAttachShader(GLuint program, GLuint shader) {
    glad_glAttachShader = (PFNGLATTACHSHADERPROC) glad_gl_on_demand_loader("glAttachShader");
    glad_glAttachShader(program, shader);
}
PFNGLATTACHSHADERPROC glad_glAttachShader = glad_on_demand_impl_glAttachShader;
static void GLAD_API_PTR glad_on_demand_impl_glBeginConditionalRender(GLuint id, GLenum mode) {
    glad_glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC) glad_gl_on_demand_loader("glBeginConditionalRender");
    glad_glBeginConditionalRender(id, mode);
}
PFNGLBEGINCONDITIONALRENDERPROC glad_glBeginConditionalRender = glad_on_demand_impl_glBeginConditionalRender;
static void GLAD_API_PTR glad_on_demand_impl_glBeginConditionalRenderNV(GLuint id, GLenum mode) {
    glad_glBeginConditionalRenderNV = (PFNGLBEGINCONDITIONALRENDERNVPROC) glad_gl_on_demand_loader("glBeginConditionalRenderNV");
    glad_glBeginConditionalRenderNV(id, mode);
}
PFNGLBEGINCONDITIONALRENDERNVPROC glad_glBeginConditionalRenderNV = glad_on_demand_impl_glBeginConditionalRenderNV;
static void GLAD_API_PTR glad_on_demand_impl_glBeginConditionalRenderNVX(GLuint id) {
    glad_glBeginConditionalRenderNVX = (PFNGLBEGINCONDITIONALRENDERNVXPROC) glad_gl_on_demand_loader("glBeginConditionalRenderNVX");
    glad_glBeginConditionalRenderNVX(id);
}
PFNGLBEGINCONDITIONALRENDERNVXPROC glad_glBeginConditionalRenderNVX = glad_on_demand_impl_glBeginConditionalRenderNVX;
static void GLAD_API_PTR glad_on_demand_impl_glBeginQuery(GLenum target, GLuint id) {
    glad_glBeginQuery = (PFNGLBEGINQUERYPROC) glad_gl_on_demand_loader("glBeginQuery");
    glad_glBeginQuery(target, id);
}
PFNGLBEGINQUERYPROC glad_glBeginQuery = glad_on_demand_impl_glBeginQuery;
static void GLAD_API_PTR glad_on_demand_impl_glBeginQueryARB(GLenum target, GLuint id) {
    glad_glBeginQueryARB = (PFNGLBEGINQUERYARBPROC) glad_gl_on_demand_loader("glBeginQueryARB");
    glad_glBeginQueryARB(target, id);
}
PFNGLBEGINQUERYARBPROC glad_glBeginQueryARB = glad_on_demand_impl_glBeginQueryARB;
static void GLAD_API_PTR glad_on_demand_impl_glBeginTransformFeedback(GLenum primitiveMode) {
    glad_glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC) glad_gl_on_demand_loader("glBeginTransformFeedback");
    glad_glBeginTransformFeedback(primitiveMode);
}
PFNGLBEGINTRANSFORMFEEDBACKPROC glad_glBeginTransformFeedback = glad_on_demand_impl_glBeginTransformFeedback;
static void GLAD_API_PTR glad_on_demand_impl_glBeginTransformFeedbackEXT(GLenum primitiveMode) {
    glad_glBeginTransformFeedbackEXT = (PFNGLBEGINTRANSFORMFEEDBACKEXTPROC) glad_gl_on_demand_loader("glBeginTransformFeedbackEXT");
    glad_glBeginTransformFeedbackEXT(primitiveMode);
}
PFNGLBEGINTRANSFORMFEEDBACKEXTPROC glad_glBeginTransformFeedbackEXT = glad_on_demand_impl_glBeginTransformFeedbackEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBeginTransformFeedbackNV(GLenum primitiveMode) {
    glad_glBeginTransformFeedbackNV = (PFNGLBEGINTRANSFORMFEEDBACKNVPROC) glad_gl_on_demand_loader("glBeginTransformFeedbackNV");
    glad_glBeginTransformFeedbackNV(primitiveMode);
}
PFNGLBEGINTRANSFORMFEEDBACKNVPROC glad_glBeginTransformFeedbackNV = glad_on_demand_impl_glBeginTransformFeedbackNV;
static void GLAD_API_PTR glad_on_demand_impl_glBindAttribLocation(GLuint program, GLuint index, const GLchar * name) {
    glad_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) glad_gl_on_demand_loader("glBindAttribLocation");
    glad_glBindAttribLocation(program, index, name);
}
PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation = glad_on_demand_impl_glBindAttribLocation;
static void GLAD_API_PTR glad_on_demand_impl_glBindAttribLocationARB(GLhandleARB programObj, GLuint index, const GLcharARB * name) {
    glad_glBindAttribLocationARB = (PFNGLBINDATTRIBLOCATIONARBPROC) glad_gl_on_demand_loader("glBindAttribLocationARB");
    glad_glBindAttribLocationARB(programObj, index, name);
}
PFNGLBINDATTRIBLOCATIONARBPROC glad_glBindAttribLocationARB = glad_on_demand_impl_glBindAttribLocationARB;
static void GLAD_API_PTR glad_on_demand_impl_glBindBuffer(GLenum target, GLuint buffer) {
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC) glad_gl_on_demand_loader("glBindBuffer");
    glad_glBindBuffer(target, buffer);
}
PFNGLBINDBUFFERPROC glad_glBindBuffer = glad_on_demand_impl_glBindBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferARB(GLenum target, GLuint buffer) {
    glad_glBindBufferARB = (PFNGLBINDBUFFERARBPROC) glad_gl_on_demand_loader("glBindBufferARB");
    glad_glBindBufferARB(target, buffer);
}
PFNGLBINDBUFFERARBPROC glad_glBindBufferARB = glad_on_demand_impl_glBindBufferARB;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferBase(GLenum target, GLuint index, GLuint buffer) {
    glad_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) glad_gl_on_demand_loader("glBindBufferBase");
    glad_glBindBufferBase(target, index, buffer);
}
PFNGLBINDBUFFERBASEPROC glad_glBindBufferBase = glad_on_demand_impl_glBindBufferBase;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferBaseEXT(GLenum target, GLuint index, GLuint buffer) {
    glad_glBindBufferBaseEXT = (PFNGLBINDBUFFERBASEEXTPROC) glad_gl_on_demand_loader("glBindBufferBaseEXT");
    glad_glBindBufferBaseEXT(target, index, buffer);
}
PFNGLBINDBUFFERBASEEXTPROC glad_glBindBufferBaseEXT = glad_on_demand_impl_glBindBufferBaseEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferBaseNV(GLenum target, GLuint index, GLuint buffer) {
    glad_glBindBufferBaseNV = (PFNGLBINDBUFFERBASENVPROC) glad_gl_on_demand_loader("glBindBufferBaseNV");
    glad_glBindBufferBaseNV(target, index, buffer);
}
PFNGLBINDBUFFERBASENVPROC glad_glBindBufferBaseNV = glad_on_demand_impl_glBindBufferBaseNV;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferOffsetEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset) {
    glad_glBindBufferOffsetEXT = (PFNGLBINDBUFFEROFFSETEXTPROC) glad_gl_on_demand_loader("glBindBufferOffsetEXT");
    glad_glBindBufferOffsetEXT(target, index, buffer, offset);
}
PFNGLBINDBUFFEROFFSETEXTPROC glad_glBindBufferOffsetEXT = glad_on_demand_impl_glBindBufferOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferOffsetNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset) {
    glad_glBindBufferOffsetNV = (PFNGLBINDBUFFEROFFSETNVPROC) glad_gl_on_demand_loader("glBindBufferOffsetNV");
    glad_glBindBufferOffsetNV(target, index, buffer, offset);
}
PFNGLBINDBUFFEROFFSETNVPROC glad_glBindBufferOffsetNV = glad_on_demand_impl_glBindBufferOffsetNV;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    glad_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) glad_gl_on_demand_loader("glBindBufferRange");
    glad_glBindBufferRange(target, index, buffer, offset, size);
}
PFNGLBINDBUFFERRANGEPROC glad_glBindBufferRange = glad_on_demand_impl_glBindBufferRange;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferRangeEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    glad_glBindBufferRangeEXT = (PFNGLBINDBUFFERRANGEEXTPROC) glad_gl_on_demand_loader("glBindBufferRangeEXT");
    glad_glBindBufferRangeEXT(target, index, buffer, offset, size);
}
PFNGLBINDBUFFERRANGEEXTPROC glad_glBindBufferRangeEXT = glad_on_demand_impl_glBindBufferRangeEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBindBufferRangeNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    glad_glBindBufferRangeNV = (PFNGLBINDBUFFERRANGENVPROC) glad_gl_on_demand_loader("glBindBufferRangeNV");
    glad_glBindBufferRangeNV(target, index, buffer, offset, size);
}
PFNGLBINDBUFFERRANGENVPROC glad_glBindBufferRangeNV = glad_on_demand_impl_glBindBufferRangeNV;
static void GLAD_API_PTR glad_on_demand_impl_glBindFragDataLocation(GLuint program, GLuint color, const GLchar * name) {
    glad_glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC) glad_gl_on_demand_loader("glBindFragDataLocation");
    glad_glBindFragDataLocation(program, color, name);
}
PFNGLBINDFRAGDATALOCATIONPROC glad_glBindFragDataLocation = glad_on_demand_impl_glBindFragDataLocation;
static void GLAD_API_PTR glad_on_demand_impl_glBindFragDataLocationEXT(GLuint program, GLuint color, const GLchar * name) {
    glad_glBindFragDataLocationEXT = (PFNGLBINDFRAGDATALOCATIONEXTPROC) glad_gl_on_demand_loader("glBindFragDataLocationEXT");
    glad_glBindFragDataLocationEXT(program, color, name);
}
PFNGLBINDFRAGDATALOCATIONEXTPROC glad_glBindFragDataLocationEXT = glad_on_demand_impl_glBindFragDataLocationEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name) {
    glad_glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) glad_gl_on_demand_loader("glBindFragDataLocationIndexed");
    glad_glBindFragDataLocationIndexed(program, colorNumber, index, name);
}
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glad_glBindFragDataLocationIndexed = glad_on_demand_impl_glBindFragDataLocationIndexed;
static void GLAD_API_PTR glad_on_demand_impl_glBindFramebuffer(GLenum target, GLuint framebuffer) {
    glad_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) glad_gl_on_demand_loader("glBindFramebuffer");
    glad_glBindFramebuffer(target, framebuffer);
}
PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer = glad_on_demand_impl_glBindFramebuffer;
static void GLAD_API_PTR glad_on_demand_impl_glBindFramebufferEXT(GLenum target, GLuint framebuffer) {
    glad_glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC) glad_gl_on_demand_loader("glBindFramebufferEXT");
    glad_glBindFramebufferEXT(target, framebuffer);
}
PFNGLBINDFRAMEBUFFEREXTPROC glad_glBindFramebufferEXT = glad_on_demand_impl_glBindFramebufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBindMultiTextureEXT(GLenum texunit, GLenum target, GLuint texture) {
    glad_glBindMultiTextureEXT = (PFNGLBINDMULTITEXTUREEXTPROC) glad_gl_on_demand_loader("glBindMultiTextureEXT");
    glad_glBindMultiTextureEXT(texunit, target, texture);
}
PFNGLBINDMULTITEXTUREEXTPROC glad_glBindMultiTextureEXT = glad_on_demand_impl_glBindMultiTextureEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBindProgramARB(GLenum target, GLuint program) {
    glad_glBindProgramARB = (PFNGLBINDPROGRAMARBPROC) glad_gl_on_demand_loader("glBindProgramARB");
    glad_glBindProgramARB(target, program);
}
PFNGLBINDPROGRAMARBPROC glad_glBindProgramARB = glad_on_demand_impl_glBindProgramARB;
static void GLAD_API_PTR glad_on_demand_impl_glBindProgramNV(GLenum target, GLuint id) {
    glad_glBindProgramNV = (PFNGLBINDPROGRAMNVPROC) glad_gl_on_demand_loader("glBindProgramNV");
    glad_glBindProgramNV(target, id);
}
PFNGLBINDPROGRAMNVPROC glad_glBindProgramNV = glad_on_demand_impl_glBindProgramNV;
static void GLAD_API_PTR glad_on_demand_impl_glBindRenderbuffer(GLenum target, GLuint renderbuffer) {
    glad_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) glad_gl_on_demand_loader("glBindRenderbuffer");
    glad_glBindRenderbuffer(target, renderbuffer);
}
PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer = glad_on_demand_impl_glBindRenderbuffer;
static void GLAD_API_PTR glad_on_demand_impl_glBindRenderbufferEXT(GLenum target, GLuint renderbuffer) {
    glad_glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC) glad_gl_on_demand_loader("glBindRenderbufferEXT");
    glad_glBindRenderbufferEXT(target, renderbuffer);
}
PFNGLBINDRENDERBUFFEREXTPROC glad_glBindRenderbufferEXT = glad_on_demand_impl_glBindRenderbufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBindSampler(GLuint unit, GLuint sampler) {
    glad_glBindSampler = (PFNGLBINDSAMPLERPROC) glad_gl_on_demand_loader("glBindSampler");
    glad_glBindSampler(unit, sampler);
}
PFNGLBINDSAMPLERPROC glad_glBindSampler = glad_on_demand_impl_glBindSampler;
static void GLAD_API_PTR glad_on_demand_impl_glBindTexture(GLenum target, GLuint texture) {
    glad_glBindTexture = (PFNGLBINDTEXTUREPROC) glad_gl_on_demand_loader("glBindTexture");
    glad_glBindTexture(target, texture);
}
PFNGLBINDTEXTUREPROC glad_glBindTexture = glad_on_demand_impl_glBindTexture;
static void GLAD_API_PTR glad_on_demand_impl_glBindTextureEXT(GLenum target, GLuint texture) {
    glad_glBindTextureEXT = (PFNGLBINDTEXTUREEXTPROC) glad_gl_on_demand_loader("glBindTextureEXT");
    glad_glBindTextureEXT(target, texture);
}
PFNGLBINDTEXTUREEXTPROC glad_glBindTextureEXT = glad_on_demand_impl_glBindTextureEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBindVertexArray(GLuint array) {
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) glad_gl_on_demand_loader("glBindVertexArray");
    glad_glBindVertexArray(array);
}
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = glad_on_demand_impl_glBindVertexArray;
static void GLAD_API_PTR glad_on_demand_impl_glBindVertexArrayAPPLE(GLuint array) {
    glad_glBindVertexArrayAPPLE = (PFNGLBINDVERTEXARRAYAPPLEPROC) glad_gl_on_demand_loader("glBindVertexArrayAPPLE");
    glad_glBindVertexArrayAPPLE(array);
}
PFNGLBINDVERTEXARRAYAPPLEPROC glad_glBindVertexArrayAPPLE = glad_on_demand_impl_glBindVertexArrayAPPLE;
static void GLAD_API_PTR glad_on_demand_impl_glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glad_glBlendColor = (PFNGLBLENDCOLORPROC) glad_gl_on_demand_loader("glBlendColor");
    glad_glBlendColor(red, green, blue, alpha);
}
PFNGLBLENDCOLORPROC glad_glBlendColor = glad_on_demand_impl_glBlendColor;
static void GLAD_API_PTR glad_on_demand_impl_glBlendColorEXT(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glad_glBlendColorEXT = (PFNGLBLENDCOLOREXTPROC) glad_gl_on_demand_loader("glBlendColorEXT");
    glad_glBlendColorEXT(red, green, blue, alpha);
}
PFNGLBLENDCOLOREXTPROC glad_glBlendColorEXT = glad_on_demand_impl_glBlendColorEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBlendEquation(GLenum mode) {
    glad_glBlendEquation = (PFNGLBLENDEQUATIONPROC) glad_gl_on_demand_loader("glBlendEquation");
    glad_glBlendEquation(mode);
}
PFNGLBLENDEQUATIONPROC glad_glBlendEquation = glad_on_demand_impl_glBlendEquation;
static void GLAD_API_PTR glad_on_demand_impl_glBlendEquationEXT(GLenum mode) {
    glad_glBlendEquationEXT = (PFNGLBLENDEQUATIONEXTPROC) glad_gl_on_demand_loader("glBlendEquationEXT");
    glad_glBlendEquationEXT(mode);
}
PFNGLBLENDEQUATIONEXTPROC glad_glBlendEquationEXT = glad_on_demand_impl_glBlendEquationEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
    glad_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) glad_gl_on_demand_loader("glBlendEquationSeparate");
    glad_glBlendEquationSeparate(modeRGB, modeAlpha);
}
PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate = glad_on_demand_impl_glBlendEquationSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glBlendEquationSeparateEXT(GLenum modeRGB, GLenum modeAlpha) {
    glad_glBlendEquationSeparateEXT = (PFNGLBLENDEQUATIONSEPARATEEXTPROC) glad_gl_on_demand_loader("glBlendEquationSeparateEXT");
    glad_glBlendEquationSeparateEXT(modeRGB, modeAlpha);
}
PFNGLBLENDEQUATIONSEPARATEEXTPROC glad_glBlendEquationSeparateEXT = glad_on_demand_impl_glBlendEquationSeparateEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBlendFunc(GLenum sfactor, GLenum dfactor) {
    glad_glBlendFunc = (PFNGLBLENDFUNCPROC) glad_gl_on_demand_loader("glBlendFunc");
    glad_glBlendFunc(sfactor, dfactor);
}
PFNGLBLENDFUNCPROC glad_glBlendFunc = glad_on_demand_impl_glBlendFunc;
static void GLAD_API_PTR glad_on_demand_impl_glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    glad_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) glad_gl_on_demand_loader("glBlendFuncSeparate");
    glad_glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}
PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate = glad_on_demand_impl_glBlendFuncSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glBlendFuncSeparateEXT(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    glad_glBlendFuncSeparateEXT = (PFNGLBLENDFUNCSEPARATEEXTPROC) glad_gl_on_demand_loader("glBlendFuncSeparateEXT");
    glad_glBlendFuncSeparateEXT(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}
PFNGLBLENDFUNCSEPARATEEXTPROC glad_glBlendFuncSeparateEXT = glad_on_demand_impl_glBlendFuncSeparateEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBlendFuncSeparateINGR(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    glad_glBlendFuncSeparateINGR = (PFNGLBLENDFUNCSEPARATEINGRPROC) glad_gl_on_demand_loader("glBlendFuncSeparateINGR");
    glad_glBlendFuncSeparateINGR(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}
PFNGLBLENDFUNCSEPARATEINGRPROC glad_glBlendFuncSeparateINGR = glad_on_demand_impl_glBlendFuncSeparateINGR;
static void GLAD_API_PTR glad_on_demand_impl_glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
    glad_glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC) glad_gl_on_demand_loader("glBlitFramebuffer");
    glad_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}
PFNGLBLITFRAMEBUFFERPROC glad_glBlitFramebuffer = glad_on_demand_impl_glBlitFramebuffer;
static void GLAD_API_PTR glad_on_demand_impl_glBlitFramebufferEXT(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
    glad_glBlitFramebufferEXT = (PFNGLBLITFRAMEBUFFEREXTPROC) glad_gl_on_demand_loader("glBlitFramebufferEXT");
    glad_glBlitFramebufferEXT(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}
PFNGLBLITFRAMEBUFFEREXTPROC glad_glBlitFramebufferEXT = glad_on_demand_impl_glBlitFramebufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage) {
    glad_glBufferData = (PFNGLBUFFERDATAPROC) glad_gl_on_demand_loader("glBufferData");
    glad_glBufferData(target, size, data, usage);
}
PFNGLBUFFERDATAPROC glad_glBufferData = glad_on_demand_impl_glBufferData;
static void GLAD_API_PTR glad_on_demand_impl_glBufferDataARB(GLenum target, GLsizeiptrARB size, const void * data, GLenum usage) {
    glad_glBufferDataARB = (PFNGLBUFFERDATAARBPROC) glad_gl_on_demand_loader("glBufferDataARB");
    glad_glBufferDataARB(target, size, data, usage);
}
PFNGLBUFFERDATAARBPROC glad_glBufferDataARB = glad_on_demand_impl_glBufferDataARB;
static void GLAD_API_PTR glad_on_demand_impl_glBufferParameteriAPPLE(GLenum target, GLenum pname, GLint param) {
    glad_glBufferParameteriAPPLE = (PFNGLBUFFERPARAMETERIAPPLEPROC) glad_gl_on_demand_loader("glBufferParameteriAPPLE");
    glad_glBufferParameteriAPPLE(target, pname, param);
}
PFNGLBUFFERPARAMETERIAPPLEPROC glad_glBufferParameteriAPPLE = glad_on_demand_impl_glBufferParameteriAPPLE;
static void GLAD_API_PTR glad_on_demand_impl_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data) {
    glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC) glad_gl_on_demand_loader("glBufferSubData");
    glad_glBufferSubData(target, offset, size, data);
}
PFNGLBUFFERSUBDATAPROC glad_glBufferSubData = glad_on_demand_impl_glBufferSubData;
static void GLAD_API_PTR glad_on_demand_impl_glBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void * data) {
    glad_glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC) glad_gl_on_demand_loader("glBufferSubDataARB");
    glad_glBufferSubDataARB(target, offset, size, data);
}
PFNGLBUFFERSUBDATAARBPROC glad_glBufferSubDataARB = glad_on_demand_impl_glBufferSubDataARB;
static GLenum GLAD_API_PTR glad_on_demand_impl_glCheckFramebufferStatus(GLenum target) {
    glad_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) glad_gl_on_demand_loader("glCheckFramebufferStatus");
    return glad_glCheckFramebufferStatus(target);
}
PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus = glad_on_demand_impl_glCheckFramebufferStatus;
static GLenum GLAD_API_PTR glad_on_demand_impl_glCheckFramebufferStatusEXT(GLenum target) {
    glad_glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) glad_gl_on_demand_loader("glCheckFramebufferStatusEXT");
    return glad_glCheckFramebufferStatusEXT(target);
}
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glad_glCheckFramebufferStatusEXT = glad_on_demand_impl_glCheckFramebufferStatusEXT;
static GLenum GLAD_API_PTR glad_on_demand_impl_glCheckNamedFramebufferStatusEXT(GLuint framebuffer, GLenum target) {
    glad_glCheckNamedFramebufferStatusEXT = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC) glad_gl_on_demand_loader("glCheckNamedFramebufferStatusEXT");
    return glad_glCheckNamedFramebufferStatusEXT(framebuffer, target);
}
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC glad_glCheckNamedFramebufferStatusEXT = glad_on_demand_impl_glCheckNamedFramebufferStatusEXT;
static void GLAD_API_PTR glad_on_demand_impl_glClampColor(GLenum target, GLenum clamp) {
    glad_glClampColor = (PFNGLCLAMPCOLORPROC) glad_gl_on_demand_loader("glClampColor");
    glad_glClampColor(target, clamp);
}
PFNGLCLAMPCOLORPROC glad_glClampColor = glad_on_demand_impl_glClampColor;
static void GLAD_API_PTR glad_on_demand_impl_glClampColorARB(GLenum target, GLenum clamp) {
    glad_glClampColorARB = (PFNGLCLAMPCOLORARBPROC) glad_gl_on_demand_loader("glClampColorARB");
    glad_glClampColorARB(target, clamp);
}
PFNGLCLAMPCOLORARBPROC glad_glClampColorARB = glad_on_demand_impl_glClampColorARB;
static void GLAD_API_PTR glad_on_demand_impl_glClear(GLbitfield mask) {
    glad_glClear = (PFNGLCLEARPROC) glad_gl_on_demand_loader("glClear");
    glad_glClear(mask);
}
PFNGLCLEARPROC glad_glClear = glad_on_demand_impl_glClear;
static void GLAD_API_PTR glad_on_demand_impl_glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
    glad_glClearBufferfi = (PFNGLCLEARBUFFERFIPROC) glad_gl_on_demand_loader("glClearBufferfi");
    glad_glClearBufferfi(buffer, drawbuffer, depth, stencil);
}
PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi = glad_on_demand_impl_glClearBufferfi;
static void GLAD_API_PTR glad_on_demand_impl_glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value) {
    glad_glClearBufferfv = (PFNGLCLEARBUFFERFVPROC) glad_gl_on_demand_loader("glClearBufferfv");
    glad_glClearBufferfv(buffer, drawbuffer, value);
}
PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv = glad_on_demand_impl_glClearBufferfv;
static void GLAD_API_PTR glad_on_demand_impl_glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value) {
    glad_glClearBufferiv = (PFNGLCLEARBUFFERIVPROC) glad_gl_on_demand_loader("glClearBufferiv");
    glad_glClearBufferiv(buffer, drawbuffer, value);
}
PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv = glad_on_demand_impl_glClearBufferiv;
static void GLAD_API_PTR glad_on_demand_impl_glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value) {
    glad_glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC) glad_gl_on_demand_loader("glClearBufferuiv");
    glad_glClearBufferuiv(buffer, drawbuffer, value);
}
PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv = glad_on_demand_impl_glClearBufferuiv;
static void GLAD_API_PTR glad_on_demand_impl_glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glad_glClearColor = (PFNGLCLEARCOLORPROC) glad_gl_on_demand_loader("glClearColor");
    glad_glClearColor(red, green, blue, alpha);
}
PFNGLCLEARCOLORPROC glad_glClearColor = glad_on_demand_impl_glClearColor;
static void GLAD_API_PTR glad_on_demand_impl_glClearColorIiEXT(GLint red, GLint green, GLint blue, GLint alpha) {
    glad_glClearColorIiEXT = (PFNGLCLEARCOLORIIEXTPROC) glad_gl_on_demand_loader("glClearColorIiEXT");
    glad_glClearColorIiEXT(red, green, blue, alpha);
}
PFNGLCLEARCOLORIIEXTPROC glad_glClearColorIiEXT = glad_on_demand_impl_glClearColorIiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glClearColorIuiEXT(GLuint red, GLuint green, GLuint blue, GLuint alpha) {
    glad_glClearColorIuiEXT = (PFNGLCLEARCOLORIUIEXTPROC) glad_gl_on_demand_loader("glClearColorIuiEXT");
    glad_glClearColorIuiEXT(red, green, blue, alpha);
}
PFNGLCLEARCOLORIUIEXTPROC glad_glClearColorIuiEXT = glad_on_demand_impl_glClearColorIuiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glClearDepth(GLdouble depth) {
    glad_glClearDepth = (PFNGLCLEARDEPTHPROC) glad_gl_on_demand_loader("glClearDepth");
    glad_glClearDepth(depth);
}
PFNGLCLEARDEPTHPROC glad_glClearDepth = glad_on_demand_impl_glClearDepth;
static void GLAD_API_PTR glad_on_demand_impl_glClearNamedBufferDataEXT(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data) {
    glad_glClearNamedBufferDataEXT = (PFNGLCLEARNAMEDBUFFERDATAEXTPROC) glad_gl_on_demand_loader("glClearNamedBufferDataEXT");
    glad_glClearNamedBufferDataEXT(buffer, internalformat, format, type, data);
}
PFNGLCLEARNAMEDBUFFERDATAEXTPROC glad_glClearNamedBufferDataEXT = glad_on_demand_impl_glClearNamedBufferDataEXT;
static void GLAD_API_PTR glad_on_demand_impl_glClearNamedBufferSubDataEXT(GLuint buffer, GLenum internalformat, GLsizeiptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data) {
    glad_glClearNamedBufferSubDataEXT = (PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC) glad_gl_on_demand_loader("glClearNamedBufferSubDataEXT");
    glad_glClearNamedBufferSubDataEXT(buffer, internalformat, offset, size, format, type, data);
}
PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC glad_glClearNamedBufferSubDataEXT = glad_on_demand_impl_glClearNamedBufferSubDataEXT;
static void GLAD_API_PTR glad_on_demand_impl_glClearStencil(GLint s) {
    glad_glClearStencil = (PFNGLCLEARSTENCILPROC) glad_gl_on_demand_loader("glClearStencil");
    glad_glClearStencil(s);
}
PFNGLCLEARSTENCILPROC glad_glClearStencil = glad_on_demand_impl_glClearStencil;
static void GLAD_API_PTR glad_on_demand_impl_glClientActiveTextureARB(GLenum texture) {
    glad_glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) glad_gl_on_demand_loader("glClientActiveTextureARB");
    glad_glClientActiveTextureARB(texture);
}
PFNGLCLIENTACTIVETEXTUREARBPROC glad_glClientActiveTextureARB = glad_on_demand_impl_glClientActiveTextureARB;
static void GLAD_API_PTR glad_on_demand_impl_glClientAttribDefaultEXT(GLbitfield mask) {
    glad_glClientAttribDefaultEXT = (PFNGLCLIENTATTRIBDEFAULTEXTPROC) glad_gl_on_demand_loader("glClientAttribDefaultEXT");
    glad_glClientAttribDefaultEXT(mask);
}
PFNGLCLIENTATTRIBDEFAULTEXTPROC glad_glClientAttribDefaultEXT = glad_on_demand_impl_glClientAttribDefaultEXT;
static GLenum GLAD_API_PTR glad_on_demand_impl_glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {
    glad_glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC) glad_gl_on_demand_loader("glClientWaitSync");
    return glad_glClientWaitSync(sync, flags, timeout);
}
PFNGLCLIENTWAITSYNCPROC glad_glClientWaitSync = glad_on_demand_impl_glClientWaitSync;
static void GLAD_API_PTR glad_on_demand_impl_glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    glad_glColorMask = (PFNGLCOLORMASKPROC) glad_gl_on_demand_loader("glColorMask");
    glad_glColorMask(red, green, blue, alpha);
}
PFNGLCOLORMASKPROC glad_glColorMask = glad_on_demand_impl_glColorMask;
static void GLAD_API_PTR glad_on_demand_impl_glColorMaskIndexedEXT(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
    glad_glColorMaskIndexedEXT = (PFNGLCOLORMASKINDEXEDEXTPROC) glad_gl_on_demand_loader("glColorMaskIndexedEXT");
    glad_glColorMaskIndexedEXT(index, r, g, b, a);
}
PFNGLCOLORMASKINDEXEDEXTPROC glad_glColorMaskIndexedEXT = glad_on_demand_impl_glColorMaskIndexedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
    glad_glColorMaski = (PFNGLCOLORMASKIPROC) glad_gl_on_demand_loader("glColorMaski");
    glad_glColorMaski(index, r, g, b, a);
}
PFNGLCOLORMASKIPROC glad_glColorMaski = glad_on_demand_impl_glColorMaski;
static void GLAD_API_PTR glad_on_demand_impl_glColorPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void * pointer) {
    glad_glColorPointerEXT = (PFNGLCOLORPOINTEREXTPROC) glad_gl_on_demand_loader("glColorPointerEXT");
    glad_glColorPointerEXT(size, type, stride, count, pointer);
}
PFNGLCOLORPOINTEREXTPROC glad_glColorPointerEXT = glad_on_demand_impl_glColorPointerEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompileShader(GLuint shader) {
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC) glad_gl_on_demand_loader("glCompileShader");
    glad_glCompileShader(shader);
}
PFNGLCOMPILESHADERPROC glad_glCompileShader = glad_on_demand_impl_glCompileShader;
static void GLAD_API_PTR glad_on_demand_impl_glCompileShaderARB(GLhandleARB shaderObj) {
    glad_glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) glad_gl_on_demand_loader("glCompileShaderARB");
    glad_glCompileShaderARB(shaderObj);
}
PFNGLCOMPILESHADERARBPROC glad_glCompileShaderARB = glad_on_demand_impl_glCompileShaderARB;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * bits) {
    glad_glCompressedMultiTexImage1DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCompressedMultiTexImage1DEXT");
    glad_glCompressedMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, imageSize, bits);
}
PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC glad_glCompressedMultiTexImage1DEXT = glad_on_demand_impl_glCompressedMultiTexImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * bits) {
    glad_glCompressedMultiTexImage2DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCompressedMultiTexImage2DEXT");
    glad_glCompressedMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, imageSize, bits);
}
PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC glad_glCompressedMultiTexImage2DEXT = glad_on_demand_impl_glCompressedMultiTexImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * bits) {
    glad_glCompressedMultiTexImage3DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC) glad_gl_on_demand_loader("glCompressedMultiTexImage3DEXT");
    glad_glCompressedMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, imageSize, bits);
}
PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC glad_glCompressedMultiTexImage3DEXT = glad_on_demand_impl_glCompressedMultiTexImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * bits) {
    glad_glCompressedMultiTexSubImage1DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCompressedMultiTexSubImage1DEXT");
    glad_glCompressedMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, imageSize, bits);
}
PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC glad_glCompressedMultiTexSubImage1DEXT = glad_on_demand_impl_glCompressedMultiTexSubImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * bits) {
    glad_glCompressedMultiTexSubImage2DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCompressedMultiTexSubImage2DEXT");
    glad_glCompressedMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, imageSize, bits);
}
PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC glad_glCompressedMultiTexSubImage2DEXT = glad_on_demand_impl_glCompressedMultiTexSubImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * bits) {
    glad_glCompressedMultiTexSubImage3DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC) glad_gl_on_demand_loader("glCompressedMultiTexSubImage3DEXT");
    glad_glCompressedMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits);
}
PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC glad_glCompressedMultiTexSubImage3DEXT = glad_on_demand_impl_glCompressedMultiTexSubImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data) {
    glad_glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC) glad_gl_on_demand_loader("glCompressedTexImage1D");
    glad_glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_glCompressedTexImage1D = glad_on_demand_impl_glCompressedTexImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexImage1DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data) {
    glad_glCompressedTexImage1DARB = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC) glad_gl_on_demand_loader("glCompressedTexImage1DARB");
    glad_glCompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC glad_glCompressedTexImage1DARB = glad_on_demand_impl_glCompressedTexImage1DARB;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data) {
    glad_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) glad_gl_on_demand_loader("glCompressedTexImage2D");
    glad_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D = glad_on_demand_impl_glCompressedTexImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexImage2DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data) {
    glad_glCompressedTexImage2DARB = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC) glad_gl_on_demand_loader("glCompressedTexImage2DARB");
    glad_glCompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glad_glCompressedTexImage2DARB = glad_on_demand_impl_glCompressedTexImage2DARB;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data) {
    glad_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) glad_gl_on_demand_loader("glCompressedTexImage3D");
    glad_glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D = glad_on_demand_impl_glCompressedTexImage3D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexImage3DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data) {
    glad_glCompressedTexImage3DARB = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC) glad_gl_on_demand_loader("glCompressedTexImage3DARB");
    glad_glCompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC glad_glCompressedTexImage3DARB = glad_on_demand_impl_glCompressedTexImage3DARB;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data) {
    glad_glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) glad_gl_on_demand_loader("glCompressedTexSubImage1D");
    glad_glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glad_glCompressedTexSubImage1D = glad_on_demand_impl_glCompressedTexSubImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexSubImage1DARB(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data) {
    glad_glCompressedTexSubImage1DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC) glad_gl_on_demand_loader("glCompressedTexSubImage1DARB");
    glad_glCompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC glad_glCompressedTexSubImage1DARB = glad_on_demand_impl_glCompressedTexSubImage1DARB;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data) {
    glad_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) glad_gl_on_demand_loader("glCompressedTexSubImage2D");
    glad_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D = glad_on_demand_impl_glCompressedTexSubImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexSubImage2DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data) {
    glad_glCompressedTexSubImage2DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC) glad_gl_on_demand_loader("glCompressedTexSubImage2DARB");
    glad_glCompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC glad_glCompressedTexSubImage2DARB = glad_on_demand_impl_glCompressedTexSubImage2DARB;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data) {
    glad_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) glad_gl_on_demand_loader("glCompressedTexSubImage3D");
    glad_glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_glCompressedTexSubImage3D = glad_on_demand_impl_glCompressedTexSubImage3D;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTexSubImage3DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data) {
    glad_glCompressedTexSubImage3DARB = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC) glad_gl_on_demand_loader("glCompressedTexSubImage3DARB");
    glad_glCompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC glad_glCompressedTexSubImage3DARB = glad_on_demand_impl_glCompressedTexSubImage3DARB;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * bits) {
    glad_glCompressedTextureImage1DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCompressedTextureImage1DEXT");
    glad_glCompressedTextureImage1DEXT(texture, target, level, internalformat, width, border, imageSize, bits);
}
PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC glad_glCompressedTextureImage1DEXT = glad_on_demand_impl_glCompressedTextureImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * bits) {
    glad_glCompressedTextureImage2DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCompressedTextureImage2DEXT");
    glad_glCompressedTextureImage2DEXT(texture, target, level, internalformat, width, height, border, imageSize, bits);
}
PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC glad_glCompressedTextureImage2DEXT = glad_on_demand_impl_glCompressedTextureImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * bits) {
    glad_glCompressedTextureImage3DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC) glad_gl_on_demand_loader("glCompressedTextureImage3DEXT");
    glad_glCompressedTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, imageSize, bits);
}
PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC glad_glCompressedTextureImage3DEXT = glad_on_demand_impl_glCompressedTextureImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * bits) {
    glad_glCompressedTextureSubImage1DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCompressedTextureSubImage1DEXT");
    glad_glCompressedTextureSubImage1DEXT(texture, target, level, xoffset, width, format, imageSize, bits);
}
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC glad_glCompressedTextureSubImage1DEXT = glad_on_demand_impl_glCompressedTextureSubImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * bits) {
    glad_glCompressedTextureSubImage2DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCompressedTextureSubImage2DEXT");
    glad_glCompressedTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, imageSize, bits);
}
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC glad_glCompressedTextureSubImage2DEXT = glad_on_demand_impl_glCompressedTextureSubImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCompressedTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * bits) {
    glad_glCompressedTextureSubImage3DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC) glad_gl_on_demand_loader("glCompressedTextureSubImage3DEXT");
    glad_glCompressedTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits);
}
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC glad_glCompressedTextureSubImage3DEXT = glad_on_demand_impl_glCompressedTextureSubImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
    glad_glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC) glad_gl_on_demand_loader("glCopyBufferSubData");
    glad_glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}
PFNGLCOPYBUFFERSUBDATAPROC glad_glCopyBufferSubData = glad_on_demand_impl_glCopyBufferSubData;
static void GLAD_API_PTR glad_on_demand_impl_glCopyMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
    glad_glCopyMultiTexImage1DEXT = (PFNGLCOPYMULTITEXIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCopyMultiTexImage1DEXT");
    glad_glCopyMultiTexImage1DEXT(texunit, target, level, internalformat, x, y, width, border);
}
PFNGLCOPYMULTITEXIMAGE1DEXTPROC glad_glCopyMultiTexImage1DEXT = glad_on_demand_impl_glCopyMultiTexImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    glad_glCopyMultiTexImage2DEXT = (PFNGLCOPYMULTITEXIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCopyMultiTexImage2DEXT");
    glad_glCopyMultiTexImage2DEXT(texunit, target, level, internalformat, x, y, width, height, border);
}
PFNGLCOPYMULTITEXIMAGE2DEXTPROC glad_glCopyMultiTexImage2DEXT = glad_on_demand_impl_glCopyMultiTexImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    glad_glCopyMultiTexSubImage1DEXT = (PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCopyMultiTexSubImage1DEXT");
    glad_glCopyMultiTexSubImage1DEXT(texunit, target, level, xoffset, x, y, width);
}
PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC glad_glCopyMultiTexSubImage1DEXT = glad_on_demand_impl_glCopyMultiTexSubImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyMultiTexSubImage2DEXT = (PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCopyMultiTexSubImage2DEXT");
    glad_glCopyMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, x, y, width, height);
}
PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC glad_glCopyMultiTexSubImage2DEXT = glad_on_demand_impl_glCopyMultiTexSubImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyMultiTexSubImage3DEXT = (PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC) glad_gl_on_demand_loader("glCopyMultiTexSubImage3DEXT");
    glad_glCopyMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, x, y, width, height);
}
PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC glad_glCopyMultiTexSubImage3DEXT = glad_on_demand_impl_glCopyMultiTexSubImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
    glad_glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC) glad_gl_on_demand_loader("glCopyTexImage1D");
    glad_glCopyTexImage1D(target, level, internalformat, x, y, width, border);
}
PFNGLCOPYTEXIMAGE1DPROC glad_glCopyTexImage1D = glad_on_demand_impl_glCopyTexImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexImage1DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
    glad_glCopyTexImage1DEXT = (PFNGLCOPYTEXIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCopyTexImage1DEXT");
    glad_glCopyTexImage1DEXT(target, level, internalformat, x, y, width, border);
}
PFNGLCOPYTEXIMAGE1DEXTPROC glad_glCopyTexImage1DEXT = glad_on_demand_impl_glCopyTexImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    glad_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) glad_gl_on_demand_loader("glCopyTexImage2D");
    glad_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}
PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D = glad_on_demand_impl_glCopyTexImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexImage2DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    glad_glCopyTexImage2DEXT = (PFNGLCOPYTEXIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCopyTexImage2DEXT");
    glad_glCopyTexImage2DEXT(target, level, internalformat, x, y, width, height, border);
}
PFNGLCOPYTEXIMAGE2DEXTPROC glad_glCopyTexImage2DEXT = glad_on_demand_impl_glCopyTexImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    glad_glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC) glad_gl_on_demand_loader("glCopyTexSubImage1D");
    glad_glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}
PFNGLCOPYTEXSUBIMAGE1DPROC glad_glCopyTexSubImage1D = glad_on_demand_impl_glCopyTexSubImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    glad_glCopyTexSubImage1DEXT = (PFNGLCOPYTEXSUBIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCopyTexSubImage1DEXT");
    glad_glCopyTexSubImage1DEXT(target, level, xoffset, x, y, width);
}
PFNGLCOPYTEXSUBIMAGE1DEXTPROC glad_glCopyTexSubImage1DEXT = glad_on_demand_impl_glCopyTexSubImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) glad_gl_on_demand_loader("glCopyTexSubImage2D");
    glad_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}
PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D = glad_on_demand_impl_glCopyTexSubImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyTexSubImage2DEXT = (PFNGLCOPYTEXSUBIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCopyTexSubImage2DEXT");
    glad_glCopyTexSubImage2DEXT(target, level, xoffset, yoffset, x, y, width, height);
}
PFNGLCOPYTEXSUBIMAGE2DEXTPROC glad_glCopyTexSubImage2DEXT = glad_on_demand_impl_glCopyTexSubImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) glad_gl_on_demand_loader("glCopyTexSubImage3D");
    glad_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}
PFNGLCOPYTEXSUBIMAGE3DPROC glad_glCopyTexSubImage3D = glad_on_demand_impl_glCopyTexSubImage3D;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyTexSubImage3DEXT = (PFNGLCOPYTEXSUBIMAGE3DEXTPROC) glad_gl_on_demand_loader("glCopyTexSubImage3DEXT");
    glad_glCopyTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}
PFNGLCOPYTEXSUBIMAGE3DEXTPROC glad_glCopyTexSubImage3DEXT = glad_on_demand_impl_glCopyTexSubImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
    glad_glCopyTextureImage1DEXT = (PFNGLCOPYTEXTUREIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCopyTextureImage1DEXT");
    glad_glCopyTextureImage1DEXT(texture, target, level, internalformat, x, y, width, border);
}
PFNGLCOPYTEXTUREIMAGE1DEXTPROC glad_glCopyTextureImage1DEXT = glad_on_demand_impl_glCopyTextureImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    glad_glCopyTextureImage2DEXT = (PFNGLCOPYTEXTUREIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCopyTextureImage2DEXT");
    glad_glCopyTextureImage2DEXT(texture, target, level, internalformat, x, y, width, height, border);
}
PFNGLCOPYTEXTUREIMAGE2DEXTPROC glad_glCopyTextureImage2DEXT = glad_on_demand_impl_glCopyTextureImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    glad_glCopyTextureSubImage1DEXT = (PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC) glad_gl_on_demand_loader("glCopyTextureSubImage1DEXT");
    glad_glCopyTextureSubImage1DEXT(texture, target, level, xoffset, x, y, width);
}
PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC glad_glCopyTextureSubImage1DEXT = glad_on_demand_impl_glCopyTextureSubImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyTextureSubImage2DEXT = (PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC) glad_gl_on_demand_loader("glCopyTextureSubImage2DEXT");
    glad_glCopyTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, x, y, width, height);
}
PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC glad_glCopyTextureSubImage2DEXT = glad_on_demand_impl_glCopyTextureSubImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glCopyTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glCopyTextureSubImage3DEXT = (PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC) glad_gl_on_demand_loader("glCopyTextureSubImage3DEXT");
    glad_glCopyTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, x, y, width, height);
}
PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC glad_glCopyTextureSubImage3DEXT = glad_on_demand_impl_glCopyTextureSubImage3DEXT;
static GLuint GLAD_API_PTR glad_on_demand_impl_glCreateProgram(void) {
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC) glad_gl_on_demand_loader("glCreateProgram");
    return glad_glCreateProgram();
}
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = glad_on_demand_impl_glCreateProgram;
static GLhandleARB GLAD_API_PTR glad_on_demand_impl_glCreateProgramObjectARB(void) {
    glad_glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) glad_gl_on_demand_loader("glCreateProgramObjectARB");
    return glad_glCreateProgramObjectARB();
}
PFNGLCREATEPROGRAMOBJECTARBPROC glad_glCreateProgramObjectARB = glad_on_demand_impl_glCreateProgramObjectARB;
static GLuint GLAD_API_PTR glad_on_demand_impl_glCreateShader(GLenum type) {
    glad_glCreateShader = (PFNGLCREATESHADERPROC) glad_gl_on_demand_loader("glCreateShader");
    return glad_glCreateShader(type);
}
PFNGLCREATESHADERPROC glad_glCreateShader = glad_on_demand_impl_glCreateShader;
static GLhandleARB GLAD_API_PTR glad_on_demand_impl_glCreateShaderObjectARB(GLenum shaderType) {
    glad_glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) glad_gl_on_demand_loader("glCreateShaderObjectARB");
    return glad_glCreateShaderObjectARB(shaderType);
}
PFNGLCREATESHADEROBJECTARBPROC glad_glCreateShaderObjectARB = glad_on_demand_impl_glCreateShaderObjectARB;
static void GLAD_API_PTR glad_on_demand_impl_glCullFace(GLenum mode) {
    glad_glCullFace = (PFNGLCULLFACEPROC) glad_gl_on_demand_loader("glCullFace");
    glad_glCullFace(mode);
}
PFNGLCULLFACEPROC glad_glCullFace = glad_on_demand_impl_glCullFace;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteBuffers(GLsizei n, const GLuint * buffers) {
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) glad_gl_on_demand_loader("glDeleteBuffers");
    glad_glDeleteBuffers(n, buffers);
}
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = glad_on_demand_impl_glDeleteBuffers;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteBuffersARB(GLsizei n, const GLuint * buffers) {
    glad_glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) glad_gl_on_demand_loader("glDeleteBuffersARB");
    glad_glDeleteBuffersARB(n, buffers);
}
PFNGLDELETEBUFFERSARBPROC glad_glDeleteBuffersARB = glad_on_demand_impl_glDeleteBuffersARB;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteFramebuffers(GLsizei n, const GLuint * framebuffers) {
    glad_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) glad_gl_on_demand_loader("glDeleteFramebuffers");
    glad_glDeleteFramebuffers(n, framebuffers);
}
PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers = glad_on_demand_impl_glDeleteFramebuffers;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteFramebuffersEXT(GLsizei n, const GLuint * framebuffers) {
    glad_glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC) glad_gl_on_demand_loader("glDeleteFramebuffersEXT");
    glad_glDeleteFramebuffersEXT(n, framebuffers);
}
PFNGLDELETEFRAMEBUFFERSEXTPROC glad_glDeleteFramebuffersEXT = glad_on_demand_impl_glDeleteFramebuffersEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteObjectARB(GLhandleARB obj) {
    glad_glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) glad_gl_on_demand_loader("glDeleteObjectARB");
    glad_glDeleteObjectARB(obj);
}
PFNGLDELETEOBJECTARBPROC glad_glDeleteObjectARB = glad_on_demand_impl_glDeleteObjectARB;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteProgram(GLuint program) {
    glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC) glad_gl_on_demand_loader("glDeleteProgram");
    glad_glDeleteProgram(program);
}
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = glad_on_demand_impl_glDeleteProgram;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteProgramsARB(GLsizei n, const GLuint * programs) {
    glad_glDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC) glad_gl_on_demand_loader("glDeleteProgramsARB");
    glad_glDeleteProgramsARB(n, programs);
}
PFNGLDELETEPROGRAMSARBPROC glad_glDeleteProgramsARB = glad_on_demand_impl_glDeleteProgramsARB;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteProgramsNV(GLsizei n, const GLuint * programs) {
    glad_glDeleteProgramsNV = (PFNGLDELETEPROGRAMSNVPROC) glad_gl_on_demand_loader("glDeleteProgramsNV");
    glad_glDeleteProgramsNV(n, programs);
}
PFNGLDELETEPROGRAMSNVPROC glad_glDeleteProgramsNV = glad_on_demand_impl_glDeleteProgramsNV;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteQueries(GLsizei n, const GLuint * ids) {
    glad_glDeleteQueries = (PFNGLDELETEQUERIESPROC) glad_gl_on_demand_loader("glDeleteQueries");
    glad_glDeleteQueries(n, ids);
}
PFNGLDELETEQUERIESPROC glad_glDeleteQueries = glad_on_demand_impl_glDeleteQueries;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteQueriesARB(GLsizei n, const GLuint * ids) {
    glad_glDeleteQueriesARB = (PFNGLDELETEQUERIESARBPROC) glad_gl_on_demand_loader("glDeleteQueriesARB");
    glad_glDeleteQueriesARB(n, ids);
}
PFNGLDELETEQUERIESARBPROC glad_glDeleteQueriesARB = glad_on_demand_impl_glDeleteQueriesARB;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers) {
    glad_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) glad_gl_on_demand_loader("glDeleteRenderbuffers");
    glad_glDeleteRenderbuffers(n, renderbuffers);
}
PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers = glad_on_demand_impl_glDeleteRenderbuffers;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteRenderbuffersEXT(GLsizei n, const GLuint * renderbuffers) {
    glad_glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC) glad_gl_on_demand_loader("glDeleteRenderbuffersEXT");
    glad_glDeleteRenderbuffersEXT(n, renderbuffers);
}
PFNGLDELETERENDERBUFFERSEXTPROC glad_glDeleteRenderbuffersEXT = glad_on_demand_impl_glDeleteRenderbuffersEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteSamplers(GLsizei count, const GLuint * samplers) {
    glad_glDeleteSamplers = (PFNGLDELETESAMPLERSPROC) glad_gl_on_demand_loader("glDeleteSamplers");
    glad_glDeleteSamplers(count, samplers);
}
PFNGLDELETESAMPLERSPROC glad_glDeleteSamplers = glad_on_demand_impl_glDeleteSamplers;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteShader(GLuint shader) {
    glad_glDeleteShader = (PFNGLDELETESHADERPROC) glad_gl_on_demand_loader("glDeleteShader");
    glad_glDeleteShader(shader);
}
PFNGLDELETESHADERPROC glad_glDeleteShader = glad_on_demand_impl_glDeleteShader;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteSync(GLsync sync) {
    glad_glDeleteSync = (PFNGLDELETESYNCPROC) glad_gl_on_demand_loader("glDeleteSync");
    glad_glDeleteSync(sync);
}
PFNGLDELETESYNCPROC glad_glDeleteSync = glad_on_demand_impl_glDeleteSync;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteTextures(GLsizei n, const GLuint * textures) {
    glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC) glad_gl_on_demand_loader("glDeleteTextures");
    glad_glDeleteTextures(n, textures);
}
PFNGLDELETETEXTURESPROC glad_glDeleteTextures = glad_on_demand_impl_glDeleteTextures;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteTexturesEXT(GLsizei n, const GLuint * textures) {
    glad_glDeleteTexturesEXT = (PFNGLDELETETEXTURESEXTPROC) glad_gl_on_demand_loader("glDeleteTexturesEXT");
    glad_glDeleteTexturesEXT(n, textures);
}
PFNGLDELETETEXTURESEXTPROC glad_glDeleteTexturesEXT = glad_on_demand_impl_glDeleteTexturesEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteVertexArrays(GLsizei n, const GLuint * arrays) {
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) glad_gl_on_demand_loader("glDeleteVertexArrays");
    glad_glDeleteVertexArrays(n, arrays);
}
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = glad_on_demand_impl_glDeleteVertexArrays;
static void GLAD_API_PTR glad_on_demand_impl_glDeleteVertexArraysAPPLE(GLsizei n, const GLuint * arrays) {
    glad_glDeleteVertexArraysAPPLE = (PFNGLDELETEVERTEXARRAYSAPPLEPROC) glad_gl_on_demand_loader("glDeleteVertexArraysAPPLE");
    glad_glDeleteVertexArraysAPPLE(n, arrays);
}
PFNGLDELETEVERTEXARRAYSAPPLEPROC glad_glDeleteVertexArraysAPPLE = glad_on_demand_impl_glDeleteVertexArraysAPPLE;
static void GLAD_API_PTR glad_on_demand_impl_glDepthFunc(GLenum func) {
    glad_glDepthFunc = (PFNGLDEPTHFUNCPROC) glad_gl_on_demand_loader("glDepthFunc");
    glad_glDepthFunc(func);
}
PFNGLDEPTHFUNCPROC glad_glDepthFunc = glad_on_demand_impl_glDepthFunc;
static void GLAD_API_PTR glad_on_demand_impl_glDepthMask(GLboolean flag) {
    glad_glDepthMask = (PFNGLDEPTHMASKPROC) glad_gl_on_demand_loader("glDepthMask");
    glad_glDepthMask(flag);
}
PFNGLDEPTHMASKPROC glad_glDepthMask = glad_on_demand_impl_glDepthMask;
static void GLAD_API_PTR glad_on_demand_impl_glDepthRange(GLdouble n, GLdouble f) {
    glad_glDepthRange = (PFNGLDEPTHRANGEPROC) glad_gl_on_demand_loader("glDepthRange");
    glad_glDepthRange(n, f);
}
PFNGLDEPTHRANGEPROC glad_glDepthRange = glad_on_demand_impl_glDepthRange;
static void GLAD_API_PTR glad_on_demand_impl_glDetachObjectARB(GLhandleARB containerObj, GLhandleARB attachedObj) {
    glad_glDetachObjectARB = (PFNGLDETACHOBJECTARBPROC) glad_gl_on_demand_loader("glDetachObjectARB");
    glad_glDetachObjectARB(containerObj, attachedObj);
}
PFNGLDETACHOBJECTARBPROC glad_glDetachObjectARB = glad_on_demand_impl_glDetachObjectARB;
static void GLAD_API_PTR glad_on_demand_impl_glDetachShader(GLuint program, GLuint shader) {
    glad_glDetachShader = (PFNGLDETACHSHADERPROC) glad_gl_on_demand_loader("glDetachShader");
    glad_glDetachShader(program, shader);
}
PFNGLDETACHSHADERPROC glad_glDetachShader = glad_on_demand_impl_glDetachShader;
static void GLAD_API_PTR glad_on_demand_impl_glDisable(GLenum cap) {
    glad_glDisable = (PFNGLDISABLEPROC) glad_gl_on_demand_loader("glDisable");
    glad_glDisable(cap);
}
PFNGLDISABLEPROC glad_glDisable = glad_on_demand_impl_glDisable;
static void GLAD_API_PTR glad_on_demand_impl_glDisableClientStateIndexedEXT(GLenum array, GLuint index) {
    glad_glDisableClientStateIndexedEXT = (PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC) glad_gl_on_demand_loader("glDisableClientStateIndexedEXT");
    glad_glDisableClientStateIndexedEXT(array, index);
}
PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC glad_glDisableClientStateIndexedEXT = glad_on_demand_impl_glDisableClientStateIndexedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDisableClientStateiEXT(GLenum array, GLuint index) {
    glad_glDisableClientStateiEXT = (PFNGLDISABLECLIENTSTATEIEXTPROC) glad_gl_on_demand_loader("glDisableClientStateiEXT");
    glad_glDisableClientStateiEXT(array, index);
}
PFNGLDISABLECLIENTSTATEIEXTPROC glad_glDisableClientStateiEXT = glad_on_demand_impl_glDisableClientStateiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDisableIndexedEXT(GLenum target, GLuint index) {
    glad_glDisableIndexedEXT = (PFNGLDISABLEINDEXEDEXTPROC) glad_gl_on_demand_loader("glDisableIndexedEXT");
    glad_glDisableIndexedEXT(target, index);
}
PFNGLDISABLEINDEXEDEXTPROC glad_glDisableIndexedEXT = glad_on_demand_impl_glDisableIndexedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDisableVertexArrayAttribEXT(GLuint vaobj, GLuint index) {
    glad_glDisableVertexArrayAttribEXT = (PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC) glad_gl_on_demand_loader("glDisableVertexArrayAttribEXT");
    glad_glDisableVertexArrayAttribEXT(vaobj, index);
}
PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC glad_glDisableVertexArrayAttribEXT = glad_on_demand_impl_glDisableVertexArrayAttribEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDisableVertexArrayEXT(GLuint vaobj, GLenum array) {
    glad_glDisableVertexArrayEXT = (PFNGLDISABLEVERTEXARRAYEXTPROC) glad_gl_on_demand_loader("glDisableVertexArrayEXT");
    glad_glDisableVertexArrayEXT(vaobj, array);
}
PFNGLDISABLEVERTEXARRAYEXTPROC glad_glDisableVertexArrayEXT = glad_on_demand_impl_glDisableVertexArrayEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDisableVertexAttribArray(GLuint index) {
    glad_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) glad_gl_on_demand_loader("glDisableVertexAttribArray");
    glad_glDisableVertexAttribArray(index);
}
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray = glad_on_demand_impl_glDisableVertexAttribArray;
static void GLAD_API_PTR glad_on_demand_impl_glDisableVertexAttribArrayARB(GLuint index) {
    glad_glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) glad_gl_on_demand_loader("glDisableVertexAttribArrayARB");
    glad_glDisableVertexAttribArrayARB(index);
}
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glad_glDisableVertexAttribArrayARB = glad_on_demand_impl_glDisableVertexAttribArrayARB;
static void GLAD_API_PTR glad_on_demand_impl_glDisablei(GLenum target, GLuint index) {
    glad_glDisablei = (PFNGLDISABLEIPROC) glad_gl_on_demand_loader("glDisablei");
    glad_glDisablei(target, index);
}
PFNGLDISABLEIPROC glad_glDisablei = glad_on_demand_impl_glDisablei;
static void GLAD_API_PTR glad_on_demand_impl_glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC) glad_gl_on_demand_loader("glDrawArrays");
    glad_glDrawArrays(mode, first, count);
}
PFNGLDRAWARRAYSPROC glad_glDrawArrays = glad_on_demand_impl_glDrawArrays;
static void GLAD_API_PTR glad_on_demand_impl_glDrawArraysEXT(GLenum mode, GLint first, GLsizei count) {
    glad_glDrawArraysEXT = (PFNGLDRAWARRAYSEXTPROC) glad_gl_on_demand_loader("glDrawArraysEXT");
    glad_glDrawArraysEXT(mode, first, count);
}
PFNGLDRAWARRAYSEXTPROC glad_glDrawArraysEXT = glad_on_demand_impl_glDrawArraysEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {
    glad_glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) glad_gl_on_demand_loader("glDrawArraysInstanced");
    glad_glDrawArraysInstanced(mode, first, count, instancecount);
}
PFNGLDRAWARRAYSINSTANCEDPROC glad_glDrawArraysInstanced = glad_on_demand_impl_glDrawArraysInstanced;
static void GLAD_API_PTR glad_on_demand_impl_glDrawArraysInstancedARB(GLenum mode, GLint first, GLsizei count, GLsizei primcount) {
    glad_glDrawArraysInstancedARB = (PFNGLDRAWARRAYSINSTANCEDARBPROC) glad_gl_on_demand_loader("glDrawArraysInstancedARB");
    glad_glDrawArraysInstancedARB(mode, first, count, primcount);
}
PFNGLDRAWARRAYSINSTANCEDARBPROC glad_glDrawArraysInstancedARB = glad_on_demand_impl_glDrawArraysInstancedARB;
static void GLAD_API_PTR glad_on_demand_impl_glDrawArraysInstancedEXT(GLenum mode, GLint start, GLsizei count, GLsizei primcount) {
    glad_glDrawArraysInstancedEXT = (PFNGLDRAWARRAYSINSTANCEDEXTPROC) glad_gl_on_demand_loader("glDrawArraysInstancedEXT");
    glad_glDrawArraysInstancedEXT(mode, start, count, primcount);
}
PFNGLDRAWARRAYSINSTANCEDEXTPROC glad_glDrawArraysInstancedEXT = glad_on_demand_impl_glDrawArraysInstancedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDrawBuffer(GLenum buf) {
    glad_glDrawBuffer = (PFNGLDRAWBUFFERPROC) glad_gl_on_demand_loader("glDrawBuffer");
    glad_glDrawBuffer(buf);
}
PFNGLDRAWBUFFERPROC glad_glDrawBuffer = glad_on_demand_impl_glDrawBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glDrawBuffers(GLsizei n, const GLenum * bufs) {
    glad_glDrawBuffers = (PFNGLDRAWBUFFERSPROC) glad_gl_on_demand_loader("glDrawBuffers");
    glad_glDrawBuffers(n, bufs);
}
PFNGLDRAWBUFFERSPROC glad_glDrawBuffers = glad_on_demand_impl_glDrawBuffers;
static void GLAD_API_PTR glad_on_demand_impl_glDrawBuffersARB(GLsizei n, const GLenum * bufs) {
    glad_glDrawBuffersARB = (PFNGLDRAWBUFFERSARBPROC) glad_gl_on_demand_loader("glDrawBuffersARB");
    glad_glDrawBuffersARB(n, bufs);
}
PFNGLDRAWBUFFERSARBPROC glad_glDrawBuffersARB = glad_on_demand_impl_glDrawBuffersARB;
static void GLAD_API_PTR glad_on_demand_impl_glDrawBuffersATI(GLsizei n, const GLenum * bufs) {
    glad_glDrawBuffersATI = (PFNGLDRAWBUFFERSATIPROC) glad_gl_on_demand_loader("glDrawBuffersATI");
    glad_glDrawBuffersATI(n, bufs);
}
PFNGLDRAWBUFFERSATIPROC glad_glDrawBuffersATI = glad_on_demand_impl_glDrawBuffersATI;
static void GLAD_API_PTR glad_on_demand_impl_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices) {
    glad_glDrawElements = (PFNGLDRAWELEMENTSPROC) glad_gl_on_demand_loader("glDrawElements");
    glad_glDrawElements(mode, count, type, indices);
}
PFNGLDRAWELEMENTSPROC glad_glDrawElements = glad_on_demand_impl_glDrawElements;
static void GLAD_API_PTR glad_on_demand_impl_glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex) {
    glad_glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC) glad_gl_on_demand_loader("glDrawElementsBaseVertex");
    glad_glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
}
PFNGLDRAWELEMENTSBASEVERTEXPROC glad_glDrawElementsBaseVertex = glad_on_demand_impl_glDrawElementsBaseVertex;
static void GLAD_API_PTR glad_on_demand_impl_glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount) {
    glad_glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) glad_gl_on_demand_loader("glDrawElementsInstanced");
    glad_glDrawElementsInstanced(mode, count, type, indices, instancecount);
}
PFNGLDRAWELEMENTSINSTANCEDPROC glad_glDrawElementsInstanced = glad_on_demand_impl_glDrawElementsInstanced;
static void GLAD_API_PTR glad_on_demand_impl_glDrawElementsInstancedARB(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei primcount) {
    glad_glDrawElementsInstancedARB = (PFNGLDRAWELEMENTSINSTANCEDARBPROC) glad_gl_on_demand_loader("glDrawElementsInstancedARB");
    glad_glDrawElementsInstancedARB(mode, count, type, indices, primcount);
}
PFNGLDRAWELEMENTSINSTANCEDARBPROC glad_glDrawElementsInstancedARB = glad_on_demand_impl_glDrawElementsInstancedARB;
static void GLAD_API_PTR glad_on_demand_impl_glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex) {
    glad_glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) glad_gl_on_demand_loader("glDrawElementsInstancedBaseVertex");
    glad_glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
}
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glad_glDrawElementsInstancedBaseVertex = glad_on_demand_impl_glDrawElementsInstancedBaseVertex;
static void GLAD_API_PTR glad_on_demand_impl_glDrawElementsInstancedEXT(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei primcount) {
    glad_glDrawElementsInstancedEXT = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC) glad_gl_on_demand_loader("glDrawElementsInstancedEXT");
    glad_glDrawElementsInstancedEXT(mode, count, type, indices, primcount);
}
PFNGLDRAWELEMENTSINSTANCEDEXTPROC glad_glDrawElementsInstancedEXT = glad_on_demand_impl_glDrawElementsInstancedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices) {
    glad_glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) glad_gl_on_demand_loader("glDrawRangeElements");
    glad_glDrawRangeElements(mode, start, end, count, type, indices);
}
PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements = glad_on_demand_impl_glDrawRangeElements;
static void GLAD_API_PTR glad_on_demand_impl_glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex) {
    glad_glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) glad_gl_on_demand_loader("glDrawRangeElementsBaseVertex");
    glad_glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
}
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glad_glDrawRangeElementsBaseVertex = glad_on_demand_impl_glDrawRangeElementsBaseVertex;
static void GLAD_API_PTR glad_on_demand_impl_glDrawRangeElementsEXT(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices) {
    glad_glDrawRangeElementsEXT = (PFNGLDRAWRANGEELEMENTSEXTPROC) glad_gl_on_demand_loader("glDrawRangeElementsEXT");
    glad_glDrawRangeElementsEXT(mode, start, end, count, type, indices);
}
PFNGLDRAWRANGEELEMENTSEXTPROC glad_glDrawRangeElementsEXT = glad_on_demand_impl_glDrawRangeElementsEXT;
static void GLAD_API_PTR glad_on_demand_impl_glEdgeFlagPointerEXT(GLsizei stride, GLsizei count, const GLboolean * pointer) {
    glad_glEdgeFlagPointerEXT = (PFNGLEDGEFLAGPOINTEREXTPROC) glad_gl_on_demand_loader("glEdgeFlagPointerEXT");
    glad_glEdgeFlagPointerEXT(stride, count, pointer);
}
PFNGLEDGEFLAGPOINTEREXTPROC glad_glEdgeFlagPointerEXT = glad_on_demand_impl_glEdgeFlagPointerEXT;
static void GLAD_API_PTR glad_on_demand_impl_glEnable(GLenum cap) {
    glad_glEnable = (PFNGLENABLEPROC) glad_gl_on_demand_loader("glEnable");
    glad_glEnable(cap);
}
PFNGLENABLEPROC glad_glEnable = glad_on_demand_impl_glEnable;
static void GLAD_API_PTR glad_on_demand_impl_glEnableClientStateIndexedEXT(GLenum array, GLuint index) {
    glad_glEnableClientStateIndexedEXT = (PFNGLENABLECLIENTSTATEINDEXEDEXTPROC) glad_gl_on_demand_loader("glEnableClientStateIndexedEXT");
    glad_glEnableClientStateIndexedEXT(array, index);
}
PFNGLENABLECLIENTSTATEINDEXEDEXTPROC glad_glEnableClientStateIndexedEXT = glad_on_demand_impl_glEnableClientStateIndexedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glEnableClientStateiEXT(GLenum array, GLuint index) {
    glad_glEnableClientStateiEXT = (PFNGLENABLECLIENTSTATEIEXTPROC) glad_gl_on_demand_loader("glEnableClientStateiEXT");
    glad_glEnableClientStateiEXT(array, index);
}
PFNGLENABLECLIENTSTATEIEXTPROC glad_glEnableClientStateiEXT = glad_on_demand_impl_glEnableClientStateiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glEnableIndexedEXT(GLenum target, GLuint index) {
    glad_glEnableIndexedEXT = (PFNGLENABLEINDEXEDEXTPROC) glad_gl_on_demand_loader("glEnableIndexedEXT");
    glad_glEnableIndexedEXT(target, index);
}
PFNGLENABLEINDEXEDEXTPROC glad_glEnableIndexedEXT = glad_on_demand_impl_glEnableIndexedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glEnableVertexArrayAttribEXT(GLuint vaobj, GLuint index) {
    glad_glEnableVertexArrayAttribEXT = (PFNGLENABLEVERTEXARRAYATTRIBEXTPROC) glad_gl_on_demand_loader("glEnableVertexArrayAttribEXT");
    glad_glEnableVertexArrayAttribEXT(vaobj, index);
}
PFNGLENABLEVERTEXARRAYATTRIBEXTPROC glad_glEnableVertexArrayAttribEXT = glad_on_demand_impl_glEnableVertexArrayAttribEXT;
static void GLAD_API_PTR glad_on_demand_impl_glEnableVertexArrayEXT(GLuint vaobj, GLenum array) {
    glad_glEnableVertexArrayEXT = (PFNGLENABLEVERTEXARRAYEXTPROC) glad_gl_on_demand_loader("glEnableVertexArrayEXT");
    glad_glEnableVertexArrayEXT(vaobj, array);
}
PFNGLENABLEVERTEXARRAYEXTPROC glad_glEnableVertexArrayEXT = glad_on_demand_impl_glEnableVertexArrayEXT;
static void GLAD_API_PTR glad_on_demand_impl_glEnableVertexAttribArray(GLuint index) {
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) glad_gl_on_demand_loader("glEnableVertexAttribArray");
    glad_glEnableVertexAttribArray(index);
}
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = glad_on_demand_impl_glEnableVertexAttribArray;
static void GLAD_API_PTR glad_on_demand_impl_glEnableVertexAttribArrayARB(GLuint index) {
    glad_glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) glad_gl_on_demand_loader("glEnableVertexAttribArrayARB");
    glad_glEnableVertexAttribArrayARB(index);
}
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glad_glEnableVertexAttribArrayARB = glad_on_demand_impl_glEnableVertexAttribArrayARB;
static void GLAD_API_PTR glad_on_demand_impl_glEnablei(GLenum target, GLuint index) {
    glad_glEnablei = (PFNGLENABLEIPROC) glad_gl_on_demand_loader("glEnablei");
    glad_glEnablei(target, index);
}
PFNGLENABLEIPROC glad_glEnablei = glad_on_demand_impl_glEnablei;
static void GLAD_API_PTR glad_on_demand_impl_glEndConditionalRender(void) {
    glad_glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC) glad_gl_on_demand_loader("glEndConditionalRender");
    glad_glEndConditionalRender();
}
PFNGLENDCONDITIONALRENDERPROC glad_glEndConditionalRender = glad_on_demand_impl_glEndConditionalRender;
static void GLAD_API_PTR glad_on_demand_impl_glEndConditionalRenderNV(void) {
    glad_glEndConditionalRenderNV = (PFNGLENDCONDITIONALRENDERNVPROC) glad_gl_on_demand_loader("glEndConditionalRenderNV");
    glad_glEndConditionalRenderNV();
}
PFNGLENDCONDITIONALRENDERNVPROC glad_glEndConditionalRenderNV = glad_on_demand_impl_glEndConditionalRenderNV;
static void GLAD_API_PTR glad_on_demand_impl_glEndConditionalRenderNVX(void) {
    glad_glEndConditionalRenderNVX = (PFNGLENDCONDITIONALRENDERNVXPROC) glad_gl_on_demand_loader("glEndConditionalRenderNVX");
    glad_glEndConditionalRenderNVX();
}
PFNGLENDCONDITIONALRENDERNVXPROC glad_glEndConditionalRenderNVX = glad_on_demand_impl_glEndConditionalRenderNVX;
static void GLAD_API_PTR glad_on_demand_impl_glEndQuery(GLenum target) {
    glad_glEndQuery = (PFNGLENDQUERYPROC) glad_gl_on_demand_loader("glEndQuery");
    glad_glEndQuery(target);
}
PFNGLENDQUERYPROC glad_glEndQuery = glad_on_demand_impl_glEndQuery;
static void GLAD_API_PTR glad_on_demand_impl_glEndQueryARB(GLenum target) {
    glad_glEndQueryARB = (PFNGLENDQUERYARBPROC) glad_gl_on_demand_loader("glEndQueryARB");
    glad_glEndQueryARB(target);
}
PFNGLENDQUERYARBPROC glad_glEndQueryARB = glad_on_demand_impl_glEndQueryARB;
static void GLAD_API_PTR glad_on_demand_impl_glEndTransformFeedback(void) {
    glad_glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC) glad_gl_on_demand_loader("glEndTransformFeedback");
    glad_glEndTransformFeedback();
}
PFNGLENDTRANSFORMFEEDBACKPROC glad_glEndTransformFeedback = glad_on_demand_impl_glEndTransformFeedback;
static void GLAD_API_PTR glad_on_demand_impl_glEndTransformFeedbackEXT(void) {
    glad_glEndTransformFeedbackEXT = (PFNGLENDTRANSFORMFEEDBACKEXTPROC) glad_gl_on_demand_loader("glEndTransformFeedbackEXT");
    glad_glEndTransformFeedbackEXT();
}
PFNGLENDTRANSFORMFEEDBACKEXTPROC glad_glEndTransformFeedbackEXT = glad_on_demand_impl_glEndTransformFeedbackEXT;
static void GLAD_API_PTR glad_on_demand_impl_glEndTransformFeedbackNV(void) {
    glad_glEndTransformFeedbackNV = (PFNGLENDTRANSFORMFEEDBACKNVPROC) glad_gl_on_demand_loader("glEndTransformFeedbackNV");
    glad_glEndTransformFeedbackNV();
}
PFNGLENDTRANSFORMFEEDBACKNVPROC glad_glEndTransformFeedbackNV = glad_on_demand_impl_glEndTransformFeedbackNV;
static void GLAD_API_PTR glad_on_demand_impl_glExecuteProgramNV(GLenum target, GLuint id, const GLfloat * params) {
    glad_glExecuteProgramNV = (PFNGLEXECUTEPROGRAMNVPROC) glad_gl_on_demand_loader("glExecuteProgramNV");
    glad_glExecuteProgramNV(target, id, params);
}
PFNGLEXECUTEPROGRAMNVPROC glad_glExecuteProgramNV = glad_on_demand_impl_glExecuteProgramNV;
static GLsync GLAD_API_PTR glad_on_demand_impl_glFenceSync(GLenum condition, GLbitfield flags) {
    glad_glFenceSync = (PFNGLFENCESYNCPROC) glad_gl_on_demand_loader("glFenceSync");
    return glad_glFenceSync(condition, flags);
}
PFNGLFENCESYNCPROC glad_glFenceSync = glad_on_demand_impl_glFenceSync;
static void GLAD_API_PTR glad_on_demand_impl_glFinish(void) {
    glad_glFinish = (PFNGLFINISHPROC) glad_gl_on_demand_loader("glFinish");
    glad_glFinish();
}
PFNGLFINISHPROC glad_glFinish = glad_on_demand_impl_glFinish;
static void GLAD_API_PTR glad_on_demand_impl_glFlush(void) {
    glad_glFlush = (PFNGLFLUSHPROC) glad_gl_on_demand_loader("glFlush");
    glad_glFlush();
}
PFNGLFLUSHPROC glad_glFlush = glad_on_demand_impl_glFlush;
static void GLAD_API_PTR glad_on_demand_impl_glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) {
    glad_glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC) glad_gl_on_demand_loader("glFlushMappedBufferRange");
    glad_glFlushMappedBufferRange(target, offset, length);
}
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_glFlushMappedBufferRange = glad_on_demand_impl_glFlushMappedBufferRange;
static void GLAD_API_PTR glad_on_demand_impl_glFlushMappedBufferRangeAPPLE(GLenum target, GLintptr offset, GLsizeiptr size) {
    glad_glFlushMappedBufferRangeAPPLE = (PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC) glad_gl_on_demand_loader("glFlushMappedBufferRangeAPPLE");
    glad_glFlushMappedBufferRangeAPPLE(target, offset, size);
}
PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC glad_glFlushMappedBufferRangeAPPLE = glad_on_demand_impl_glFlushMappedBufferRangeAPPLE;
static void GLAD_API_PTR glad_on_demand_impl_glFlushMappedNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length) {
    glad_glFlushMappedNamedBufferRangeEXT = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC) glad_gl_on_demand_loader("glFlushMappedNamedBufferRangeEXT");
    glad_glFlushMappedNamedBufferRangeEXT(buffer, offset, length);
}
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC glad_glFlushMappedNamedBufferRangeEXT = glad_on_demand_impl_glFlushMappedNamedBufferRangeEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferDrawBufferEXT(GLuint framebuffer, GLenum mode) {
    glad_glFramebufferDrawBufferEXT = (PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC) glad_gl_on_demand_loader("glFramebufferDrawBufferEXT");
    glad_glFramebufferDrawBufferEXT(framebuffer, mode);
}
PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC glad_glFramebufferDrawBufferEXT = glad_on_demand_impl_glFramebufferDrawBufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferDrawBuffersEXT(GLuint framebuffer, GLsizei n, const GLenum * bufs) {
    glad_glFramebufferDrawBuffersEXT = (PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC) glad_gl_on_demand_loader("glFramebufferDrawBuffersEXT");
    glad_glFramebufferDrawBuffersEXT(framebuffer, n, bufs);
}
PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC glad_glFramebufferDrawBuffersEXT = glad_on_demand_impl_glFramebufferDrawBuffersEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferReadBufferEXT(GLuint framebuffer, GLenum mode) {
    glad_glFramebufferReadBufferEXT = (PFNGLFRAMEBUFFERREADBUFFEREXTPROC) glad_gl_on_demand_loader("glFramebufferReadBufferEXT");
    glad_glFramebufferReadBufferEXT(framebuffer, mode);
}
PFNGLFRAMEBUFFERREADBUFFEREXTPROC glad_glFramebufferReadBufferEXT = glad_on_demand_impl_glFramebufferReadBufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    glad_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) glad_gl_on_demand_loader("glFramebufferRenderbuffer");
    glad_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}
PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer = glad_on_demand_impl_glFramebufferRenderbuffer;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferRenderbufferEXT(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    glad_glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC) glad_gl_on_demand_loader("glFramebufferRenderbufferEXT");
    glad_glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer);
}
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glad_glFramebufferRenderbufferEXT = glad_on_demand_impl_glFramebufferRenderbufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {
    glad_glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC) glad_gl_on_demand_loader("glFramebufferTexture");
    glad_glFramebufferTexture(target, attachment, texture, level);
}
PFNGLFRAMEBUFFERTEXTUREPROC glad_glFramebufferTexture = glad_on_demand_impl_glFramebufferTexture;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glad_glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) glad_gl_on_demand_loader("glFramebufferTexture1D");
    glad_glFramebufferTexture1D(target, attachment, textarget, texture, level);
}
PFNGLFRAMEBUFFERTEXTURE1DPROC glad_glFramebufferTexture1D = glad_on_demand_impl_glFramebufferTexture1D;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture1DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glad_glFramebufferTexture1DEXT = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC) glad_gl_on_demand_loader("glFramebufferTexture1DEXT");
    glad_glFramebufferTexture1DEXT(target, attachment, textarget, texture, level);
}
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glad_glFramebufferTexture1DEXT = glad_on_demand_impl_glFramebufferTexture1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glad_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) glad_gl_on_demand_loader("glFramebufferTexture2D");
    glad_glFramebufferTexture2D(target, attachment, textarget, texture, level);
}
PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D = glad_on_demand_impl_glFramebufferTexture2D;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture2DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glad_glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) glad_gl_on_demand_loader("glFramebufferTexture2DEXT");
    glad_glFramebufferTexture2DEXT(target, attachment, textarget, texture, level);
}
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glad_glFramebufferTexture2DEXT = glad_on_demand_impl_glFramebufferTexture2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) {
    glad_glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) glad_gl_on_demand_loader("glFramebufferTexture3D");
    glad_glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
}
PFNGLFRAMEBUFFERTEXTURE3DPROC glad_glFramebufferTexture3D = glad_on_demand_impl_glFramebufferTexture3D;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTexture3DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) {
    glad_glFramebufferTexture3DEXT = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC) glad_gl_on_demand_loader("glFramebufferTexture3DEXT");
    glad_glFramebufferTexture3DEXT(target, attachment, textarget, texture, level, zoffset);
}
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glad_glFramebufferTexture3DEXT = glad_on_demand_impl_glFramebufferTexture3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTextureARB(GLenum target, GLenum attachment, GLuint texture, GLint level) {
    glad_glFramebufferTextureARB = (PFNGLFRAMEBUFFERTEXTUREARBPROC) glad_gl_on_demand_loader("glFramebufferTextureARB");
    glad_glFramebufferTextureARB(target, attachment, texture, level);
}
PFNGLFRAMEBUFFERTEXTUREARBPROC glad_glFramebufferTextureARB = glad_on_demand_impl_glFramebufferTextureARB;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTextureEXT(GLenum target, GLenum attachment, GLuint texture, GLint level) {
    glad_glFramebufferTextureEXT = (PFNGLFRAMEBUFFERTEXTUREEXTPROC) glad_gl_on_demand_loader("glFramebufferTextureEXT");
    glad_glFramebufferTextureEXT(target, attachment, texture, level);
}
PFNGLFRAMEBUFFERTEXTUREEXTPROC glad_glFramebufferTextureEXT = glad_on_demand_impl_glFramebufferTextureEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTextureFaceARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face) {
    glad_glFramebufferTextureFaceARB = (PFNGLFRAMEBUFFERTEXTUREFACEARBPROC) glad_gl_on_demand_loader("glFramebufferTextureFaceARB");
    glad_glFramebufferTextureFaceARB(target, attachment, texture, level, face);
}
PFNGLFRAMEBUFFERTEXTUREFACEARBPROC glad_glFramebufferTextureFaceARB = glad_on_demand_impl_glFramebufferTextureFaceARB;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTextureFaceEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face) {
    glad_glFramebufferTextureFaceEXT = (PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC) glad_gl_on_demand_loader("glFramebufferTextureFaceEXT");
    glad_glFramebufferTextureFaceEXT(target, attachment, texture, level, face);
}
PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC glad_glFramebufferTextureFaceEXT = glad_on_demand_impl_glFramebufferTextureFaceEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
    glad_glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) glad_gl_on_demand_loader("glFramebufferTextureLayer");
    glad_glFramebufferTextureLayer(target, attachment, texture, level, layer);
}
PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_glFramebufferTextureLayer = glad_on_demand_impl_glFramebufferTextureLayer;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTextureLayerARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
    glad_glFramebufferTextureLayerARB = (PFNGLFRAMEBUFFERTEXTURELAYERARBPROC) glad_gl_on_demand_loader("glFramebufferTextureLayerARB");
    glad_glFramebufferTextureLayerARB(target, attachment, texture, level, layer);
}
PFNGLFRAMEBUFFERTEXTURELAYERARBPROC glad_glFramebufferTextureLayerARB = glad_on_demand_impl_glFramebufferTextureLayerARB;
static void GLAD_API_PTR glad_on_demand_impl_glFramebufferTextureLayerEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
    glad_glFramebufferTextureLayerEXT = (PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC) glad_gl_on_demand_loader("glFramebufferTextureLayerEXT");
    glad_glFramebufferTextureLayerEXT(target, attachment, texture, level, layer);
}
PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC glad_glFramebufferTextureLayerEXT = glad_on_demand_impl_glFramebufferTextureLayerEXT;
static void GLAD_API_PTR glad_on_demand_impl_glFrontFace(GLenum mode) {
    glad_glFrontFace = (PFNGLFRONTFACEPROC) glad_gl_on_demand_loader("glFrontFace");
    glad_glFrontFace(mode);
}
PFNGLFRONTFACEPROC glad_glFrontFace = glad_on_demand_impl_glFrontFace;
static void GLAD_API_PTR glad_on_demand_impl_glGenBuffers(GLsizei n, GLuint * buffers) {
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC) glad_gl_on_demand_loader("glGenBuffers");
    glad_glGenBuffers(n, buffers);
}
PFNGLGENBUFFERSPROC glad_glGenBuffers = glad_on_demand_impl_glGenBuffers;
static void GLAD_API_PTR glad_on_demand_impl_glGenBuffersARB(GLsizei n, GLuint * buffers) {
    glad_glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) glad_gl_on_demand_loader("glGenBuffersARB");
    glad_glGenBuffersARB(n, buffers);
}
PFNGLGENBUFFERSARBPROC glad_glGenBuffersARB = glad_on_demand_impl_glGenBuffersARB;
static void GLAD_API_PTR glad_on_demand_impl_glGenFramebuffers(GLsizei n, GLuint * framebuffers) {
    glad_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) glad_gl_on_demand_loader("glGenFramebuffers");
    glad_glGenFramebuffers(n, framebuffers);
}
PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers = glad_on_demand_impl_glGenFramebuffers;
static void GLAD_API_PTR glad_on_demand_impl_glGenFramebuffersEXT(GLsizei n, GLuint * framebuffers) {
    glad_glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC) glad_gl_on_demand_loader("glGenFramebuffersEXT");
    glad_glGenFramebuffersEXT(n, framebuffers);
}
PFNGLGENFRAMEBUFFERSEXTPROC glad_glGenFramebuffersEXT = glad_on_demand_impl_glGenFramebuffersEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGenProgramsARB(GLsizei n, GLuint * programs) {
    glad_glGenProgramsARB = (PFNGLGENPROGRAMSARBPROC) glad_gl_on_demand_loader("glGenProgramsARB");
    glad_glGenProgramsARB(n, programs);
}
PFNGLGENPROGRAMSARBPROC glad_glGenProgramsARB = glad_on_demand_impl_glGenProgramsARB;
static void GLAD_API_PTR glad_on_demand_impl_glGenProgramsNV(GLsizei n, GLuint * programs) {
    glad_glGenProgramsNV = (PFNGLGENPROGRAMSNVPROC) glad_gl_on_demand_loader("glGenProgramsNV");
    glad_glGenProgramsNV(n, programs);
}
PFNGLGENPROGRAMSNVPROC glad_glGenProgramsNV = glad_on_demand_impl_glGenProgramsNV;
static void GLAD_API_PTR glad_on_demand_impl_glGenQueries(GLsizei n, GLuint * ids) {
    glad_glGenQueries = (PFNGLGENQUERIESPROC) glad_gl_on_demand_loader("glGenQueries");
    glad_glGenQueries(n, ids);
}
PFNGLGENQUERIESPROC glad_glGenQueries = glad_on_demand_impl_glGenQueries;
static void GLAD_API_PTR glad_on_demand_impl_glGenQueriesARB(GLsizei n, GLuint * ids) {
    glad_glGenQueriesARB = (PFNGLGENQUERIESARBPROC) glad_gl_on_demand_loader("glGenQueriesARB");
    glad_glGenQueriesARB(n, ids);
}
PFNGLGENQUERIESARBPROC glad_glGenQueriesARB = glad_on_demand_impl_glGenQueriesARB;
static void GLAD_API_PTR glad_on_demand_impl_glGenRenderbuffers(GLsizei n, GLuint * renderbuffers) {
    glad_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) glad_gl_on_demand_loader("glGenRenderbuffers");
    glad_glGenRenderbuffers(n, renderbuffers);
}
PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers = glad_on_demand_impl_glGenRenderbuffers;
static void GLAD_API_PTR glad_on_demand_impl_glGenRenderbuffersEXT(GLsizei n, GLuint * renderbuffers) {
    glad_glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC) glad_gl_on_demand_loader("glGenRenderbuffersEXT");
    glad_glGenRenderbuffersEXT(n, renderbuffers);
}
PFNGLGENRENDERBUFFERSEXTPROC glad_glGenRenderbuffersEXT = glad_on_demand_impl_glGenRenderbuffersEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGenSamplers(GLsizei count, GLuint * samplers) {
    glad_glGenSamplers = (PFNGLGENSAMPLERSPROC) glad_gl_on_demand_loader("glGenSamplers");
    glad_glGenSamplers(count, samplers);
}
PFNGLGENSAMPLERSPROC glad_glGenSamplers = glad_on_demand_impl_glGenSamplers;
static void GLAD_API_PTR glad_on_demand_impl_glGenTextures(GLsizei n, GLuint * textures) {
    glad_glGenTextures = (PFNGLGENTEXTURESPROC) glad_gl_on_demand_loader("glGenTextures");
    glad_glGenTextures(n, textures);
}
PFNGLGENTEXTURESPROC glad_glGenTextures = glad_on_demand_impl_glGenTextures;
static void GLAD_API_PTR glad_on_demand_impl_glGenTexturesEXT(GLsizei n, GLuint * textures) {
    glad_glGenTexturesEXT = (PFNGLGENTEXTURESEXTPROC) glad_gl_on_demand_loader("glGenTexturesEXT");
    glad_glGenTexturesEXT(n, textures);
}
PFNGLGENTEXTURESEXTPROC glad_glGenTexturesEXT = glad_on_demand_impl_glGenTexturesEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGenVertexArrays(GLsizei n, GLuint * arrays) {
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) glad_gl_on_demand_loader("glGenVertexArrays");
    glad_glGenVertexArrays(n, arrays);
}
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = glad_on_demand_impl_glGenVertexArrays;
static void GLAD_API_PTR glad_on_demand_impl_glGenVertexArraysAPPLE(GLsizei n, GLuint * arrays) {
    glad_glGenVertexArraysAPPLE = (PFNGLGENVERTEXARRAYSAPPLEPROC) glad_gl_on_demand_loader("glGenVertexArraysAPPLE");
    glad_glGenVertexArraysAPPLE(n, arrays);
}
PFNGLGENVERTEXARRAYSAPPLEPROC glad_glGenVertexArraysAPPLE = glad_on_demand_impl_glGenVertexArraysAPPLE;
static void GLAD_API_PTR glad_on_demand_impl_glGenerateMipmap(GLenum target) {
    glad_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) glad_gl_on_demand_loader("glGenerateMipmap");
    glad_glGenerateMipmap(target);
}
PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap = glad_on_demand_impl_glGenerateMipmap;
static void GLAD_API_PTR glad_on_demand_impl_glGenerateMipmapEXT(GLenum target) {
    glad_glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXTPROC) glad_gl_on_demand_loader("glGenerateMipmapEXT");
    glad_glGenerateMipmapEXT(target);
}
PFNGLGENERATEMIPMAPEXTPROC glad_glGenerateMipmapEXT = glad_on_demand_impl_glGenerateMipmapEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGenerateMultiTexMipmapEXT(GLenum texunit, GLenum target) {
    glad_glGenerateMultiTexMipmapEXT = (PFNGLGENERATEMULTITEXMIPMAPEXTPROC) glad_gl_on_demand_loader("glGenerateMultiTexMipmapEXT");
    glad_glGenerateMultiTexMipmapEXT(texunit, target);
}
PFNGLGENERATEMULTITEXMIPMAPEXTPROC glad_glGenerateMultiTexMipmapEXT = glad_on_demand_impl_glGenerateMultiTexMipmapEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGenerateTextureMipmapEXT(GLuint texture, GLenum target) {
    glad_glGenerateTextureMipmapEXT = (PFNGLGENERATETEXTUREMIPMAPEXTPROC) glad_gl_on_demand_loader("glGenerateTextureMipmapEXT");
    glad_glGenerateTextureMipmapEXT(texture, target);
}
PFNGLGENERATETEXTUREMIPMAPEXTPROC glad_glGenerateTextureMipmapEXT = glad_on_demand_impl_glGenerateTextureMipmapEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) {
    glad_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC) glad_gl_on_demand_loader("glGetActiveAttrib");
    glad_glGetActiveAttrib(program, index, bufSize, length, size, type, name);
}
PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib = glad_on_demand_impl_glGetActiveAttrib;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveAttribARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name) {
    glad_glGetActiveAttribARB = (PFNGLGETACTIVEATTRIBARBPROC) glad_gl_on_demand_loader("glGetActiveAttribARB");
    glad_glGetActiveAttribARB(programObj, index, maxLength, length, size, type, name);
}
PFNGLGETACTIVEATTRIBARBPROC glad_glGetActiveAttribARB = glad_on_demand_impl_glGetActiveAttribARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) {
    glad_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC) glad_gl_on_demand_loader("glGetActiveUniform");
    glad_glGetActiveUniform(program, index, bufSize, length, size, type, name);
}
PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform = glad_on_demand_impl_glGetActiveUniform;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveUniformARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name) {
    glad_glGetActiveUniformARB = (PFNGLGETACTIVEUNIFORMARBPROC) glad_gl_on_demand_loader("glGetActiveUniformARB");
    glad_glGetActiveUniformARB(programObj, index, maxLength, length, size, type, name);
}
PFNGLGETACTIVEUNIFORMARBPROC glad_glGetActiveUniformARB = glad_on_demand_impl_glGetActiveUniformARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName) {
    glad_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) glad_gl_on_demand_loader("glGetActiveUniformBlockName");
    glad_glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glad_glGetActiveUniformBlockName = glad_on_demand_impl_glGetActiveUniformBlockName;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params) {
    glad_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC) glad_gl_on_demand_loader("glGetActiveUniformBlockiv");
    glad_glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
}
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glad_glGetActiveUniformBlockiv = glad_on_demand_impl_glGetActiveUniformBlockiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName) {
    glad_glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC) glad_gl_on_demand_loader("glGetActiveUniformName");
    glad_glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
}
PFNGLGETACTIVEUNIFORMNAMEPROC glad_glGetActiveUniformName = glad_on_demand_impl_glGetActiveUniformName;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params) {
    glad_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC) glad_gl_on_demand_loader("glGetActiveUniformsiv");
    glad_glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
}
PFNGLGETACTIVEUNIFORMSIVPROC glad_glGetActiveUniformsiv = glad_on_demand_impl_glGetActiveUniformsiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetActiveVaryingNV(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name) {
    glad_glGetActiveVaryingNV = (PFNGLGETACTIVEVARYINGNVPROC) glad_gl_on_demand_loader("glGetActiveVaryingNV");
    glad_glGetActiveVaryingNV(program, index, bufSize, length, size, type, name);
}
PFNGLGETACTIVEVARYINGNVPROC glad_glGetActiveVaryingNV = glad_on_demand_impl_glGetActiveVaryingNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetAttachedObjectsARB(GLhandleARB containerObj, GLsizei maxCount, GLsizei * count, GLhandleARB * obj) {
    glad_glGetAttachedObjectsARB = (PFNGLGETATTACHEDOBJECTSARBPROC) glad_gl_on_demand_loader("glGetAttachedObjectsARB");
    glad_glGetAttachedObjectsARB(containerObj, maxCount, count, obj);
}
PFNGLGETATTACHEDOBJECTSARBPROC glad_glGetAttachedObjectsARB = glad_on_demand_impl_glGetAttachedObjectsARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders) {
    glad_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC) glad_gl_on_demand_loader("glGetAttachedShaders");
    glad_glGetAttachedShaders(program, maxCount, count, shaders);
}
PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders = glad_on_demand_impl_glGetAttachedShaders;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetAttribLocation(GLuint program, const GLchar * name) {
    glad_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) glad_gl_on_demand_loader("glGetAttribLocation");
    return glad_glGetAttribLocation(program, name);
}
PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation = glad_on_demand_impl_glGetAttribLocation;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetAttribLocationARB(GLhandleARB programObj, const GLcharARB * name) {
    glad_glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC) glad_gl_on_demand_loader("glGetAttribLocationARB");
    return glad_glGetAttribLocationARB(programObj, name);
}
PFNGLGETATTRIBLOCATIONARBPROC glad_glGetAttribLocationARB = glad_on_demand_impl_glGetAttribLocationARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetBooleanIndexedvEXT(GLenum target, GLuint index, GLboolean * data) {
    glad_glGetBooleanIndexedvEXT = (PFNGLGETBOOLEANINDEXEDVEXTPROC) glad_gl_on_demand_loader("glGetBooleanIndexedvEXT");
    glad_glGetBooleanIndexedvEXT(target, index, data);
}
PFNGLGETBOOLEANINDEXEDVEXTPROC glad_glGetBooleanIndexedvEXT = glad_on_demand_impl_glGetBooleanIndexedvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetBooleani_v(GLenum target, GLuint index, GLboolean * data) {
    glad_glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC) glad_gl_on_demand_loader("glGetBooleani_v");
    glad_glGetBooleani_v(target, index, data);
}
PFNGLGETBOOLEANI_VPROC glad_glGetBooleani_v = glad_on_demand_impl_glGetBooleani_v;
static void GLAD_API_PTR glad_on_demand_impl_glGetBooleanv(GLenum pname, GLboolean * data) {
    glad_glGetBooleanv = (PFNGLGETBOOLEANVPROC) glad_gl_on_demand_loader("glGetBooleanv");
    glad_glGetBooleanv(pname, data);
}
PFNGLGETBOOLEANVPROC glad_glGetBooleanv = glad_on_demand_impl_glGetBooleanv;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params) {
    glad_glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC) glad_gl_on_demand_loader("glGetBufferParameteri64v");
    glad_glGetBufferParameteri64v(target, pname, params);
}
PFNGLGETBUFFERPARAMETERI64VPROC glad_glGetBufferParameteri64v = glad_on_demand_impl_glGetBufferParameteri64v;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferParameteriv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) glad_gl_on_demand_loader("glGetBufferParameteriv");
    glad_glGetBufferParameteriv(target, pname, params);
}
PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv = glad_on_demand_impl_glGetBufferParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferParameterivARB(GLenum target, GLenum pname, GLint * params) {
    glad_glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) glad_gl_on_demand_loader("glGetBufferParameterivARB");
    glad_glGetBufferParameterivARB(target, pname, params);
}
PFNGLGETBUFFERPARAMETERIVARBPROC glad_glGetBufferParameterivARB = glad_on_demand_impl_glGetBufferParameterivARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferPointerv(GLenum target, GLenum pname, void ** params) {
    glad_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) glad_gl_on_demand_loader("glGetBufferPointerv");
    glad_glGetBufferPointerv(target, pname, params);
}
PFNGLGETBUFFERPOINTERVPROC glad_glGetBufferPointerv = glad_on_demand_impl_glGetBufferPointerv;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferPointervARB(GLenum target, GLenum pname, void ** params) {
    glad_glGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC) glad_gl_on_demand_loader("glGetBufferPointervARB");
    glad_glGetBufferPointervARB(target, pname, params);
}
PFNGLGETBUFFERPOINTERVARBPROC glad_glGetBufferPointervARB = glad_on_demand_impl_glGetBufferPointervARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data) {
    glad_glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) glad_gl_on_demand_loader("glGetBufferSubData");
    glad_glGetBufferSubData(target, offset, size, data);
}
PFNGLGETBUFFERSUBDATAPROC glad_glGetBufferSubData = glad_on_demand_impl_glGetBufferSubData;
static void GLAD_API_PTR glad_on_demand_impl_glGetBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, void * data) {
    glad_glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC) glad_gl_on_demand_loader("glGetBufferSubDataARB");
    glad_glGetBufferSubDataARB(target, offset, size, data);
}
PFNGLGETBUFFERSUBDATAARBPROC glad_glGetBufferSubDataARB = glad_on_demand_impl_glGetBufferSubDataARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetCompressedMultiTexImageEXT(GLenum texunit, GLenum target, GLint lod, void * img) {
    glad_glGetCompressedMultiTexImageEXT = (PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC) glad_gl_on_demand_loader("glGetCompressedMultiTexImageEXT");
    glad_glGetCompressedMultiTexImageEXT(texunit, target, lod, img);
}
PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC glad_glGetCompressedMultiTexImageEXT = glad_on_demand_impl_glGetCompressedMultiTexImageEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetCompressedTexImage(GLenum target, GLint level, void * img) {
    glad_glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC) glad_gl_on_demand_loader("glGetCompressedTexImage");
    glad_glGetCompressedTexImage(target, level, img);
}
PFNGLGETCOMPRESSEDTEXIMAGEPROC glad_glGetCompressedTexImage = glad_on_demand_impl_glGetCompressedTexImage;
static void GLAD_API_PTR glad_on_demand_impl_glGetCompressedTexImageARB(GLenum target, GLint level, void * img) {
    glad_glGetCompressedTexImageARB = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC) glad_gl_on_demand_loader("glGetCompressedTexImageARB");
    glad_glGetCompressedTexImageARB(target, level, img);
}
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC glad_glGetCompressedTexImageARB = glad_on_demand_impl_glGetCompressedTexImageARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetCompressedTextureImageEXT(GLuint texture, GLenum target, GLint lod, void * img) {
    glad_glGetCompressedTextureImageEXT = (PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC) glad_gl_on_demand_loader("glGetCompressedTextureImageEXT");
    glad_glGetCompressedTextureImageEXT(texture, target, lod, img);
}
PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC glad_glGetCompressedTextureImageEXT = glad_on_demand_impl_glGetCompressedTextureImageEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetDoubleIndexedvEXT(GLenum target, GLuint index, GLdouble * data) {
    glad_glGetDoubleIndexedvEXT = (PFNGLGETDOUBLEINDEXEDVEXTPROC) glad_gl_on_demand_loader("glGetDoubleIndexedvEXT");
    glad_glGetDoubleIndexedvEXT(target, index, data);
}
PFNGLGETDOUBLEINDEXEDVEXTPROC glad_glGetDoubleIndexedvEXT = glad_on_demand_impl_glGetDoubleIndexedvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetDoublei_vEXT(GLenum pname, GLuint index, GLdouble * params) {
    glad_glGetDoublei_vEXT = (PFNGLGETDOUBLEI_VEXTPROC) glad_gl_on_demand_loader("glGetDoublei_vEXT");
    glad_glGetDoublei_vEXT(pname, index, params);
}
PFNGLGETDOUBLEI_VEXTPROC glad_glGetDoublei_vEXT = glad_on_demand_impl_glGetDoublei_vEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetDoublev(GLenum pname, GLdouble * data) {
    glad_glGetDoublev = (PFNGLGETDOUBLEVPROC) glad_gl_on_demand_loader("glGetDoublev");
    glad_glGetDoublev(pname, data);
}
PFNGLGETDOUBLEVPROC glad_glGetDoublev = glad_on_demand_impl_glGetDoublev;
static GLenum GLAD_API_PTR glad_on_demand_impl_glGetError(void) {
    glad_glGetError = (PFNGLGETERRORPROC) glad_gl_on_demand_loader("glGetError");
    return glad_glGetError();
}
PFNGLGETERRORPROC glad_glGetError = glad_on_demand_impl_glGetError;
static void GLAD_API_PTR glad_on_demand_impl_glGetFloatIndexedvEXT(GLenum target, GLuint index, GLfloat * data) {
    glad_glGetFloatIndexedvEXT = (PFNGLGETFLOATINDEXEDVEXTPROC) glad_gl_on_demand_loader("glGetFloatIndexedvEXT");
    glad_glGetFloatIndexedvEXT(target, index, data);
}
PFNGLGETFLOATINDEXEDVEXTPROC glad_glGetFloatIndexedvEXT = glad_on_demand_impl_glGetFloatIndexedvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetFloati_vEXT(GLenum pname, GLuint index, GLfloat * params) {
    glad_glGetFloati_vEXT = (PFNGLGETFLOATI_VEXTPROC) glad_gl_on_demand_loader("glGetFloati_vEXT");
    glad_glGetFloati_vEXT(pname, index, params);
}
PFNGLGETFLOATI_VEXTPROC glad_glGetFloati_vEXT = glad_on_demand_impl_glGetFloati_vEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetFloatv(GLenum pname, GLfloat * data) {
    glad_glGetFloatv = (PFNGLGETFLOATVPROC) glad_gl_on_demand_loader("glGetFloatv");
    glad_glGetFloatv(pname, data);
}
PFNGLGETFLOATVPROC glad_glGetFloatv = glad_on_demand_impl_glGetFloatv;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetFragDataIndex(GLuint program, const GLchar * name) {
    glad_glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC) glad_gl_on_demand_loader("glGetFragDataIndex");
    return glad_glGetFragDataIndex(program, name);
}
PFNGLGETFRAGDATAINDEXPROC glad_glGetFragDataIndex = glad_on_demand_impl_glGetFragDataIndex;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetFragDataLocation(GLuint program, const GLchar * name) {
    glad_glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC) glad_gl_on_demand_loader("glGetFragDataLocation");
    return glad_glGetFragDataLocation(program, name);
}
PFNGLGETFRAGDATALOCATIONPROC glad_glGetFragDataLocation = glad_on_demand_impl_glGetFragDataLocation;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetFragDataLocationEXT(GLuint program, const GLchar * name) {
    glad_glGetFragDataLocationEXT = (PFNGLGETFRAGDATALOCATIONEXTPROC) glad_gl_on_demand_loader("glGetFragDataLocationEXT");
    return glad_glGetFragDataLocationEXT(program, name);
}
PFNGLGETFRAGDATALOCATIONEXTPROC glad_glGetFragDataLocationEXT = glad_on_demand_impl_glGetFragDataLocationEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params) {
    glad_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) glad_gl_on_demand_loader("glGetFramebufferAttachmentParameteriv");
    glad_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv = glad_on_demand_impl_glGetFramebufferAttachmentParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetFramebufferAttachmentParameterivEXT(GLenum target, GLenum attachment, GLenum pname, GLint * params) {
    glad_glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetFramebufferAttachmentParameterivEXT");
    glad_glGetFramebufferAttachmentParameterivEXT(target, attachment, pname, params);
}
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glad_glGetFramebufferAttachmentParameterivEXT = glad_on_demand_impl_glGetFramebufferAttachmentParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint * params) {
    glad_glGetFramebufferParameterivEXT = (PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetFramebufferParameterivEXT");
    glad_glGetFramebufferParameterivEXT(framebuffer, pname, params);
}
PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC glad_glGetFramebufferParameterivEXT = glad_on_demand_impl_glGetFramebufferParameterivEXT;
static GLhandleARB GLAD_API_PTR glad_on_demand_impl_glGetHandleARB(GLenum pname) {
    glad_glGetHandleARB = (PFNGLGETHANDLEARBPROC) glad_gl_on_demand_loader("glGetHandleARB");
    return glad_glGetHandleARB(pname);
}
PFNGLGETHANDLEARBPROC glad_glGetHandleARB = glad_on_demand_impl_glGetHandleARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetInfoLogARB(GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * infoLog) {
    glad_glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) glad_gl_on_demand_loader("glGetInfoLogARB");
    glad_glGetInfoLogARB(obj, maxLength, length, infoLog);
}
PFNGLGETINFOLOGARBPROC glad_glGetInfoLogARB = glad_on_demand_impl_glGetInfoLogARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetInteger64i_v(GLenum target, GLuint index, GLint64 * data) {
    glad_glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC) glad_gl_on_demand_loader("glGetInteger64i_v");
    glad_glGetInteger64i_v(target, index, data);
}
PFNGLGETINTEGER64I_VPROC glad_glGetInteger64i_v = glad_on_demand_impl_glGetInteger64i_v;
static void GLAD_API_PTR glad_on_demand_impl_glGetInteger64v(GLenum pname, GLint64 * data) {
    glad_glGetInteger64v = (PFNGLGETINTEGER64VPROC) glad_gl_on_demand_loader("glGetInteger64v");
    glad_glGetInteger64v(pname, data);
}
PFNGLGETINTEGER64VPROC glad_glGetInteger64v = glad_on_demand_impl_glGetInteger64v;
static void GLAD_API_PTR glad_on_demand_impl_glGetIntegerIndexedvEXT(GLenum target, GLuint index, GLint * data) {
    glad_glGetIntegerIndexedvEXT = (PFNGLGETINTEGERINDEXEDVEXTPROC) glad_gl_on_demand_loader("glGetIntegerIndexedvEXT");
    glad_glGetIntegerIndexedvEXT(target, index, data);
}
PFNGLGETINTEGERINDEXEDVEXTPROC glad_glGetIntegerIndexedvEXT = glad_on_demand_impl_glGetIntegerIndexedvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetIntegeri_v(GLenum target, GLuint index, GLint * data) {
    glad_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) glad_gl_on_demand_loader("glGetIntegeri_v");
    glad_glGetIntegeri_v(target, index, data);
}
PFNGLGETINTEGERI_VPROC glad_glGetIntegeri_v = glad_on_demand_impl_glGetIntegeri_v;
static void GLAD_API_PTR glad_on_demand_impl_glGetIntegerv(GLenum pname, GLint * data) {
    glad_glGetIntegerv = (PFNGLGETINTEGERVPROC) glad_gl_on_demand_loader("glGetIntegerv");
    glad_glGetIntegerv(pname, data);
}
PFNGLGETINTEGERVPROC glad_glGetIntegerv = glad_on_demand_impl_glGetIntegerv;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat * params) {
    glad_glGetMultiTexEnvfvEXT = (PFNGLGETMULTITEXENVFVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexEnvfvEXT");
    glad_glGetMultiTexEnvfvEXT(texunit, target, pname, params);
}
PFNGLGETMULTITEXENVFVEXTPROC glad_glGetMultiTexEnvfvEXT = glad_on_demand_impl_glGetMultiTexEnvfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, GLint * params) {
    glad_glGetMultiTexEnvivEXT = (PFNGLGETMULTITEXENVIVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexEnvivEXT");
    glad_glGetMultiTexEnvivEXT(texunit, target, pname, params);
}
PFNGLGETMULTITEXENVIVEXTPROC glad_glGetMultiTexEnvivEXT = glad_on_demand_impl_glGetMultiTexEnvivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble * params) {
    glad_glGetMultiTexGendvEXT = (PFNGLGETMULTITEXGENDVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexGendvEXT");
    glad_glGetMultiTexGendvEXT(texunit, coord, pname, params);
}
PFNGLGETMULTITEXGENDVEXTPROC glad_glGetMultiTexGendvEXT = glad_on_demand_impl_glGetMultiTexGendvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat * params) {
    glad_glGetMultiTexGenfvEXT = (PFNGLGETMULTITEXGENFVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexGenfvEXT");
    glad_glGetMultiTexGenfvEXT(texunit, coord, pname, params);
}
PFNGLGETMULTITEXGENFVEXTPROC glad_glGetMultiTexGenfvEXT = glad_on_demand_impl_glGetMultiTexGenfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, GLint * params) {
    glad_glGetMultiTexGenivEXT = (PFNGLGETMULTITEXGENIVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexGenivEXT");
    glad_glGetMultiTexGenivEXT(texunit, coord, pname, params);
}
PFNGLGETMULTITEXGENIVEXTPROC glad_glGetMultiTexGenivEXT = glad_on_demand_impl_glGetMultiTexGenivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexImageEXT(GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void * pixels) {
    glad_glGetMultiTexImageEXT = (PFNGLGETMULTITEXIMAGEEXTPROC) glad_gl_on_demand_loader("glGetMultiTexImageEXT");
    glad_glGetMultiTexImageEXT(texunit, target, level, format, type, pixels);
}
PFNGLGETMULTITEXIMAGEEXTPROC glad_glGetMultiTexImageEXT = glad_on_demand_impl_glGetMultiTexImageEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexLevelParameterfvEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat * params) {
    glad_glGetMultiTexLevelParameterfvEXT = (PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexLevelParameterfvEXT");
    glad_glGetMultiTexLevelParameterfvEXT(texunit, target, level, pname, params);
}
PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC glad_glGetMultiTexLevelParameterfvEXT = glad_on_demand_impl_glGetMultiTexLevelParameterfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexLevelParameterivEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLint * params) {
    glad_glGetMultiTexLevelParameterivEXT = (PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexLevelParameterivEXT");
    glad_glGetMultiTexLevelParameterivEXT(texunit, target, level, pname, params);
}
PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC glad_glGetMultiTexLevelParameterivEXT = glad_on_demand_impl_glGetMultiTexLevelParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, GLint * params) {
    glad_glGetMultiTexParameterIivEXT = (PFNGLGETMULTITEXPARAMETERIIVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexParameterIivEXT");
    glad_glGetMultiTexParameterIivEXT(texunit, target, pname, params);
}
PFNGLGETMULTITEXPARAMETERIIVEXTPROC glad_glGetMultiTexParameterIivEXT = glad_on_demand_impl_glGetMultiTexParameterIivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, GLuint * params) {
    glad_glGetMultiTexParameterIuivEXT = (PFNGLGETMULTITEXPARAMETERIUIVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexParameterIuivEXT");
    glad_glGetMultiTexParameterIuivEXT(texunit, target, pname, params);
}
PFNGLGETMULTITEXPARAMETERIUIVEXTPROC glad_glGetMultiTexParameterIuivEXT = glad_on_demand_impl_glGetMultiTexParameterIuivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat * params) {
    glad_glGetMultiTexParameterfvEXT = (PFNGLGETMULTITEXPARAMETERFVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexParameterfvEXT");
    glad_glGetMultiTexParameterfvEXT(texunit, target, pname, params);
}
PFNGLGETMULTITEXPARAMETERFVEXTPROC glad_glGetMultiTexParameterfvEXT = glad_on_demand_impl_glGetMultiTexParameterfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, GLint * params) {
    glad_glGetMultiTexParameterivEXT = (PFNGLGETMULTITEXPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetMultiTexParameterivEXT");
    glad_glGetMultiTexParameterivEXT(texunit, target, pname, params);
}
PFNGLGETMULTITEXPARAMETERIVEXTPROC glad_glGetMultiTexParameterivEXT = glad_on_demand_impl_glGetMultiTexParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultisamplefv(GLenum pname, GLuint index, GLfloat * val) {
    glad_glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC) glad_gl_on_demand_loader("glGetMultisamplefv");
    glad_glGetMultisamplefv(pname, index, val);
}
PFNGLGETMULTISAMPLEFVPROC glad_glGetMultisamplefv = glad_on_demand_impl_glGetMultisamplefv;
static void GLAD_API_PTR glad_on_demand_impl_glGetMultisamplefvNV(GLenum pname, GLuint index, GLfloat * val) {
    glad_glGetMultisamplefvNV = (PFNGLGETMULTISAMPLEFVNVPROC) glad_gl_on_demand_loader("glGetMultisamplefvNV");
    glad_glGetMultisamplefvNV(pname, index, val);
}
PFNGLGETMULTISAMPLEFVNVPROC glad_glGetMultisamplefvNV = glad_on_demand_impl_glGetMultisamplefvNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedBufferParameterivEXT(GLuint buffer, GLenum pname, GLint * params) {
    glad_glGetNamedBufferParameterivEXT = (PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetNamedBufferParameterivEXT");
    glad_glGetNamedBufferParameterivEXT(buffer, pname, params);
}
PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC glad_glGetNamedBufferParameterivEXT = glad_on_demand_impl_glGetNamedBufferParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedBufferPointervEXT(GLuint buffer, GLenum pname, void ** params) {
    glad_glGetNamedBufferPointervEXT = (PFNGLGETNAMEDBUFFERPOINTERVEXTPROC) glad_gl_on_demand_loader("glGetNamedBufferPointervEXT");
    glad_glGetNamedBufferPointervEXT(buffer, pname, params);
}
PFNGLGETNAMEDBUFFERPOINTERVEXTPROC glad_glGetNamedBufferPointervEXT = glad_on_demand_impl_glGetNamedBufferPointervEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data) {
    glad_glGetNamedBufferSubDataEXT = (PFNGLGETNAMEDBUFFERSUBDATAEXTPROC) glad_gl_on_demand_loader("glGetNamedBufferSubDataEXT");
    glad_glGetNamedBufferSubDataEXT(buffer, offset, size, data);
}
PFNGLGETNAMEDBUFFERSUBDATAEXTPROC glad_glGetNamedBufferSubDataEXT = glad_on_demand_impl_glGetNamedBufferSubDataEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedFramebufferAttachmentParameterivEXT(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params) {
    glad_glGetNamedFramebufferAttachmentParameterivEXT = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetNamedFramebufferAttachmentParameterivEXT");
    glad_glGetNamedFramebufferAttachmentParameterivEXT(framebuffer, attachment, pname, params);
}
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glad_glGetNamedFramebufferAttachmentParameterivEXT = glad_on_demand_impl_glGetNamedFramebufferAttachmentParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint * params) {
    glad_glGetNamedFramebufferParameterivEXT = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetNamedFramebufferParameterivEXT");
    glad_glGetNamedFramebufferParameterivEXT(framebuffer, pname, params);
}
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC glad_glGetNamedFramebufferParameterivEXT = glad_on_demand_impl_glGetNamedFramebufferParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedProgramLocalParameterIivEXT(GLuint program, GLenum target, GLuint index, GLint * params) {
    glad_glGetNamedProgramLocalParameterIivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC) glad_gl_on_demand_loader("glGetNamedProgramLocalParameterIivEXT");
    glad_glGetNamedProgramLocalParameterIivEXT(program, target, index, params);
}
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC glad_glGetNamedProgramLocalParameterIivEXT = glad_on_demand_impl_glGetNamedProgramLocalParameterIivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedProgramLocalParameterIuivEXT(GLuint program, GLenum target, GLuint index, GLuint * params) {
    glad_glGetNamedProgramLocalParameterIuivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC) glad_gl_on_demand_loader("glGetNamedProgramLocalParameterIuivEXT");
    glad_glGetNamedProgramLocalParameterIuivEXT(program, target, index, params);
}
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC glad_glGetNamedProgramLocalParameterIuivEXT = glad_on_demand_impl_glGetNamedProgramLocalParameterIuivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedProgramLocalParameterdvEXT(GLuint program, GLenum target, GLuint index, GLdouble * params) {
    glad_glGetNamedProgramLocalParameterdvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC) glad_gl_on_demand_loader("glGetNamedProgramLocalParameterdvEXT");
    glad_glGetNamedProgramLocalParameterdvEXT(program, target, index, params);
}
PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC glad_glGetNamedProgramLocalParameterdvEXT = glad_on_demand_impl_glGetNamedProgramLocalParameterdvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedProgramLocalParameterfvEXT(GLuint program, GLenum target, GLuint index, GLfloat * params) {
    glad_glGetNamedProgramLocalParameterfvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC) glad_gl_on_demand_loader("glGetNamedProgramLocalParameterfvEXT");
    glad_glGetNamedProgramLocalParameterfvEXT(program, target, index, params);
}
PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC glad_glGetNamedProgramLocalParameterfvEXT = glad_on_demand_impl_glGetNamedProgramLocalParameterfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedProgramStringEXT(GLuint program, GLenum target, GLenum pname, void * string) {
    glad_glGetNamedProgramStringEXT = (PFNGLGETNAMEDPROGRAMSTRINGEXTPROC) glad_gl_on_demand_loader("glGetNamedProgramStringEXT");
    glad_glGetNamedProgramStringEXT(program, target, pname, string);
}
PFNGLGETNAMEDPROGRAMSTRINGEXTPROC glad_glGetNamedProgramStringEXT = glad_on_demand_impl_glGetNamedProgramStringEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedProgramivEXT(GLuint program, GLenum target, GLenum pname, GLint * params) {
    glad_glGetNamedProgramivEXT = (PFNGLGETNAMEDPROGRAMIVEXTPROC) glad_gl_on_demand_loader("glGetNamedProgramivEXT");
    glad_glGetNamedProgramivEXT(program, target, pname, params);
}
PFNGLGETNAMEDPROGRAMIVEXTPROC glad_glGetNamedProgramivEXT = glad_on_demand_impl_glGetNamedProgramivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetNamedRenderbufferParameterivEXT(GLuint renderbuffer, GLenum pname, GLint * params) {
    glad_glGetNamedRenderbufferParameterivEXT = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetNamedRenderbufferParameterivEXT");
    glad_glGetNamedRenderbufferParameterivEXT(renderbuffer, pname, params);
}
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC glad_glGetNamedRenderbufferParameterivEXT = glad_on_demand_impl_glGetNamedRenderbufferParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetObjectParameterfvARB(GLhandleARB obj, GLenum pname, GLfloat * params) {
    glad_glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC) glad_gl_on_demand_loader("glGetObjectParameterfvARB");
    glad_glGetObjectParameterfvARB(obj, pname, params);
}
PFNGLGETOBJECTPARAMETERFVARBPROC glad_glGetObjectParameterfvARB = glad_on_demand_impl_glGetObjectParameterfvARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetObjectParameterivARB(GLhandleARB obj, GLenum pname, GLint * params) {
    glad_glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) glad_gl_on_demand_loader("glGetObjectParameterivARB");
    glad_glGetObjectParameterivARB(obj, pname, params);
}
PFNGLGETOBJECTPARAMETERIVARBPROC glad_glGetObjectParameterivARB = glad_on_demand_impl_glGetObjectParameterivARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetPointerIndexedvEXT(GLenum target, GLuint index, void ** data) {
    glad_glGetPointerIndexedvEXT = (PFNGLGETPOINTERINDEXEDVEXTPROC) glad_gl_on_demand_loader("glGetPointerIndexedvEXT");
    glad_glGetPointerIndexedvEXT(target, index, data);
}
PFNGLGETPOINTERINDEXEDVEXTPROC glad_glGetPointerIndexedvEXT = glad_on_demand_impl_glGetPointerIndexedvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetPointeri_vEXT(GLenum pname, GLuint index, void ** params) {
    glad_glGetPointeri_vEXT = (PFNGLGETPOINTERI_VEXTPROC) glad_gl_on_demand_loader("glGetPointeri_vEXT");
    glad_glGetPointeri_vEXT(pname, index, params);
}
PFNGLGETPOINTERI_VEXTPROC glad_glGetPointeri_vEXT = glad_on_demand_impl_glGetPointeri_vEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetPointervEXT(GLenum pname, void ** params) {
    glad_glGetPointervEXT = (PFNGLGETPOINTERVEXTPROC) glad_gl_on_demand_loader("glGetPointervEXT");
    glad_glGetPointervEXT(pname, params);
}
PFNGLGETPOINTERVEXTPROC glad_glGetPointervEXT = glad_on_demand_impl_glGetPointervEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramEnvParameterdvARB(GLenum target, GLuint index, GLdouble * params) {
    glad_glGetProgramEnvParameterdvARB = (PFNGLGETPROGRAMENVPARAMETERDVARBPROC) glad_gl_on_demand_loader("glGetProgramEnvParameterdvARB");
    glad_glGetProgramEnvParameterdvARB(target, index, params);
}
PFNGLGETPROGRAMENVPARAMETERDVARBPROC glad_glGetProgramEnvParameterdvARB = glad_on_demand_impl_glGetProgramEnvParameterdvARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramEnvParameterfvARB(GLenum target, GLuint index, GLfloat * params) {
    glad_glGetProgramEnvParameterfvARB = (PFNGLGETPROGRAMENVPARAMETERFVARBPROC) glad_gl_on_demand_loader("glGetProgramEnvParameterfvARB");
    glad_glGetProgramEnvParameterfvARB(target, index, params);
}
PFNGLGETPROGRAMENVPARAMETERFVARBPROC glad_glGetProgramEnvParameterfvARB = glad_on_demand_impl_glGetProgramEnvParameterfvARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog) {
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) glad_gl_on_demand_loader("glGetProgramInfoLog");
    glad_glGetProgramInfoLog(program, bufSize, length, infoLog);
}
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = glad_on_demand_impl_glGetProgramInfoLog;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramLocalParameterdvARB(GLenum target, GLuint index, GLdouble * params) {
    glad_glGetProgramLocalParameterdvARB = (PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC) glad_gl_on_demand_loader("glGetProgramLocalParameterdvARB");
    glad_glGetProgramLocalParameterdvARB(target, index, params);
}
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC glad_glGetProgramLocalParameterdvARB = glad_on_demand_impl_glGetProgramLocalParameterdvARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramLocalParameterfvARB(GLenum target, GLuint index, GLfloat * params) {
    glad_glGetProgramLocalParameterfvARB = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC) glad_gl_on_demand_loader("glGetProgramLocalParameterfvARB");
    glad_glGetProgramLocalParameterfvARB(target, index, params);
}
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC glad_glGetProgramLocalParameterfvARB = glad_on_demand_impl_glGetProgramLocalParameterfvARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramParameterdvNV(GLenum target, GLuint index, GLenum pname, GLdouble * params) {
    glad_glGetProgramParameterdvNV = (PFNGLGETPROGRAMPARAMETERDVNVPROC) glad_gl_on_demand_loader("glGetProgramParameterdvNV");
    glad_glGetProgramParameterdvNV(target, index, pname, params);
}
PFNGLGETPROGRAMPARAMETERDVNVPROC glad_glGetProgramParameterdvNV = glad_on_demand_impl_glGetProgramParameterdvNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat * params) {
    glad_glGetProgramParameterfvNV = (PFNGLGETPROGRAMPARAMETERFVNVPROC) glad_gl_on_demand_loader("glGetProgramParameterfvNV");
    glad_glGetProgramParameterfvNV(target, index, pname, params);
}
PFNGLGETPROGRAMPARAMETERFVNVPROC glad_glGetProgramParameterfvNV = glad_on_demand_impl_glGetProgramParameterfvNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramStringARB(GLenum target, GLenum pname, void * string) {
    glad_glGetProgramStringARB = (PFNGLGETPROGRAMSTRINGARBPROC) glad_gl_on_demand_loader("glGetProgramStringARB");
    glad_glGetProgramStringARB(target, pname, string);
}
PFNGLGETPROGRAMSTRINGARBPROC glad_glGetProgramStringARB = glad_on_demand_impl_glGetProgramStringARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramStringNV(GLuint id, GLenum pname, GLubyte * program) {
    glad_glGetProgramStringNV = (PFNGLGETPROGRAMSTRINGNVPROC) glad_gl_on_demand_loader("glGetProgramStringNV");
    glad_glGetProgramStringNV(id, pname, program);
}
PFNGLGETPROGRAMSTRINGNVPROC glad_glGetProgramStringNV = glad_on_demand_impl_glGetProgramStringNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramiv(GLuint program, GLenum pname, GLint * params) {
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC) glad_gl_on_demand_loader("glGetProgramiv");
    glad_glGetProgramiv(program, pname, params);
}
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = glad_on_demand_impl_glGetProgramiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramivARB(GLenum target, GLenum pname, GLint * params) {
    glad_glGetProgramivARB = (PFNGLGETPROGRAMIVARBPROC) glad_gl_on_demand_loader("glGetProgramivARB");
    glad_glGetProgramivARB(target, pname, params);
}
PFNGLGETPROGRAMIVARBPROC glad_glGetProgramivARB = glad_on_demand_impl_glGetProgramivARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetProgramivNV(GLuint id, GLenum pname, GLint * params) {
    glad_glGetProgramivNV = (PFNGLGETPROGRAMIVNVPROC) glad_gl_on_demand_loader("glGetProgramivNV");
    glad_glGetProgramivNV(id, pname, params);
}
PFNGLGETPROGRAMIVNVPROC glad_glGetProgramivNV = glad_on_demand_impl_glGetProgramivNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params) {
    glad_glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC) glad_gl_on_demand_loader("glGetQueryObjecti64v");
    glad_glGetQueryObjecti64v(id, pname, params);
}
PFNGLGETQUERYOBJECTI64VPROC glad_glGetQueryObjecti64v = glad_on_demand_impl_glGetQueryObjecti64v;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjecti64vEXT(GLuint id, GLenum pname, GLint64 * params) {
    glad_glGetQueryObjecti64vEXT = (PFNGLGETQUERYOBJECTI64VEXTPROC) glad_gl_on_demand_loader("glGetQueryObjecti64vEXT");
    glad_glGetQueryObjecti64vEXT(id, pname, params);
}
PFNGLGETQUERYOBJECTI64VEXTPROC glad_glGetQueryObjecti64vEXT = glad_on_demand_impl_glGetQueryObjecti64vEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params) {
    glad_glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC) glad_gl_on_demand_loader("glGetQueryObjectiv");
    glad_glGetQueryObjectiv(id, pname, params);
}
PFNGLGETQUERYOBJECTIVPROC glad_glGetQueryObjectiv = glad_on_demand_impl_glGetQueryObjectiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjectivARB(GLuint id, GLenum pname, GLint * params) {
    glad_glGetQueryObjectivARB = (PFNGLGETQUERYOBJECTIVARBPROC) glad_gl_on_demand_loader("glGetQueryObjectivARB");
    glad_glGetQueryObjectivARB(id, pname, params);
}
PFNGLGETQUERYOBJECTIVARBPROC glad_glGetQueryObjectivARB = glad_on_demand_impl_glGetQueryObjectivARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params) {
    glad_glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC) glad_gl_on_demand_loader("glGetQueryObjectui64v");
    glad_glGetQueryObjectui64v(id, pname, params);
}
PFNGLGETQUERYOBJECTUI64VPROC glad_glGetQueryObjectui64v = glad_on_demand_impl_glGetQueryObjectui64v;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjectui64vEXT(GLuint id, GLenum pname, GLuint64 * params) {
    glad_glGetQueryObjectui64vEXT = (PFNGLGETQUERYOBJECTUI64VEXTPROC) glad_gl_on_demand_loader("glGetQueryObjectui64vEXT");
    glad_glGetQueryObjectui64vEXT(id, pname, params);
}
PFNGLGETQUERYOBJECTUI64VEXTPROC glad_glGetQueryObjectui64vEXT = glad_on_demand_impl_glGetQueryObjectui64vEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params) {
    glad_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC) glad_gl_on_demand_loader("glGetQueryObjectuiv");
    glad_glGetQueryObjectuiv(id, pname, params);
}
PFNGLGETQUERYOBJECTUIVPROC glad_glGetQueryObjectuiv = glad_on_demand_impl_glGetQueryObjectuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryObjectuivARB(GLuint id, GLenum pname, GLuint * params) {
    glad_glGetQueryObjectuivARB = (PFNGLGETQUERYOBJECTUIVARBPROC) glad_gl_on_demand_loader("glGetQueryObjectuivARB");
    glad_glGetQueryObjectuivARB(id, pname, params);
}
PFNGLGETQUERYOBJECTUIVARBPROC glad_glGetQueryObjectuivARB = glad_on_demand_impl_glGetQueryObjectuivARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryiv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetQueryiv = (PFNGLGETQUERYIVPROC) glad_gl_on_demand_loader("glGetQueryiv");
    glad_glGetQueryiv(target, pname, params);
}
PFNGLGETQUERYIVPROC glad_glGetQueryiv = glad_on_demand_impl_glGetQueryiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetQueryivARB(GLenum target, GLenum pname, GLint * params) {
    glad_glGetQueryivARB = (PFNGLGETQUERYIVARBPROC) glad_gl_on_demand_loader("glGetQueryivARB");
    glad_glGetQueryivARB(target, pname, params);
}
PFNGLGETQUERYIVARBPROC glad_glGetQueryivARB = glad_on_demand_impl_glGetQueryivARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) glad_gl_on_demand_loader("glGetRenderbufferParameteriv");
    glad_glGetRenderbufferParameteriv(target, pname, params);
}
PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv = glad_on_demand_impl_glGetRenderbufferParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetRenderbufferParameterivEXT(GLenum target, GLenum pname, GLint * params) {
    glad_glGetRenderbufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetRenderbufferParameterivEXT");
    glad_glGetRenderbufferParameterivEXT(target, pname, params);
}
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glad_glGetRenderbufferParameterivEXT = glad_on_demand_impl_glGetRenderbufferParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params) {
    glad_glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC) glad_gl_on_demand_loader("glGetSamplerParameterIiv");
    glad_glGetSamplerParameterIiv(sampler, pname, params);
}
PFNGLGETSAMPLERPARAMETERIIVPROC glad_glGetSamplerParameterIiv = glad_on_demand_impl_glGetSamplerParameterIiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params) {
    glad_glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC) glad_gl_on_demand_loader("glGetSamplerParameterIuiv");
    glad_glGetSamplerParameterIuiv(sampler, pname, params);
}
PFNGLGETSAMPLERPARAMETERIUIVPROC glad_glGetSamplerParameterIuiv = glad_on_demand_impl_glGetSamplerParameterIuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params) {
    glad_glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC) glad_gl_on_demand_loader("glGetSamplerParameterfv");
    glad_glGetSamplerParameterfv(sampler, pname, params);
}
PFNGLGETSAMPLERPARAMETERFVPROC glad_glGetSamplerParameterfv = glad_on_demand_impl_glGetSamplerParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params) {
    glad_glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC) glad_gl_on_demand_loader("glGetSamplerParameteriv");
    glad_glGetSamplerParameteriv(sampler, pname, params);
}
PFNGLGETSAMPLERPARAMETERIVPROC glad_glGetSamplerParameteriv = glad_on_demand_impl_glGetSamplerParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog) {
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glad_gl_on_demand_loader("glGetShaderInfoLog");
    glad_glGetShaderInfoLog(shader, bufSize, length, infoLog);
}
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = glad_on_demand_impl_glGetShaderInfoLog;
static void GLAD_API_PTR glad_on_demand_impl_glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source) {
    glad_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC) glad_gl_on_demand_loader("glGetShaderSource");
    glad_glGetShaderSource(shader, bufSize, length, source);
}
PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource = glad_on_demand_impl_glGetShaderSource;
static void GLAD_API_PTR glad_on_demand_impl_glGetShaderSourceARB(GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * source) {
    glad_glGetShaderSourceARB = (PFNGLGETSHADERSOURCEARBPROC) glad_gl_on_demand_loader("glGetShaderSourceARB");
    glad_glGetShaderSourceARB(obj, maxLength, length, source);
}
PFNGLGETSHADERSOURCEARBPROC glad_glGetShaderSourceARB = glad_on_demand_impl_glGetShaderSourceARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetShaderiv(GLuint shader, GLenum pname, GLint * params) {
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC) glad_gl_on_demand_loader("glGetShaderiv");
    glad_glGetShaderiv(shader, pname, params);
}
PFNGLGETSHADERIVPROC glad_glGetShaderiv = glad_on_demand_impl_glGetShaderiv;
static const GLubyte * GLAD_API_PTR glad_on_demand_impl_glGetString(GLenum name) {
    glad_glGetString = (PFNGLGETSTRINGPROC) glad_gl_on_demand_loader("glGetString");
    return glad_glGetString(name);
}
PFNGLGETSTRINGPROC glad_glGetString = glad_on_demand_impl_glGetString;
static const GLubyte * GLAD_API_PTR glad_on_demand_impl_glGetStringi(GLenum name, GLuint index) {
    glad_glGetStringi = (PFNGLGETSTRINGIPROC) glad_gl_on_demand_loader("glGetStringi");
    return glad_glGetStringi(name, index);
}
PFNGLGETSTRINGIPROC glad_glGetStringi = glad_on_demand_impl_glGetStringi;
static void GLAD_API_PTR glad_on_demand_impl_glGetSynciv(GLsync sync, GLenum pname, GLsizei count, GLsizei * length, GLint * values) {
    glad_glGetSynciv = (PFNGLGETSYNCIVPROC) glad_gl_on_demand_loader("glGetSynciv");
    glad_glGetSynciv(sync, pname, count, length, values);
}
PFNGLGETSYNCIVPROC glad_glGetSynciv = glad_on_demand_impl_glGetSynciv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels) {
    glad_glGetTexImage = (PFNGLGETTEXIMAGEPROC) glad_gl_on_demand_loader("glGetTexImage");
    glad_glGetTexImage(target, level, format, type, pixels);
}
PFNGLGETTEXIMAGEPROC glad_glGetTexImage = glad_on_demand_impl_glGetTexImage;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params) {
    glad_glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC) glad_gl_on_demand_loader("glGetTexLevelParameterfv");
    glad_glGetTexLevelParameterfv(target, level, pname, params);
}
PFNGLGETTEXLEVELPARAMETERFVPROC glad_glGetTexLevelParameterfv = glad_on_demand_impl_glGetTexLevelParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params) {
    glad_glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC) glad_gl_on_demand_loader("glGetTexLevelParameteriv");
    glad_glGetTexLevelParameteriv(target, level, pname, params);
}
PFNGLGETTEXLEVELPARAMETERIVPROC glad_glGetTexLevelParameteriv = glad_on_demand_impl_glGetTexLevelParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameterIiv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC) glad_gl_on_demand_loader("glGetTexParameterIiv");
    glad_glGetTexParameterIiv(target, pname, params);
}
PFNGLGETTEXPARAMETERIIVPROC glad_glGetTexParameterIiv = glad_on_demand_impl_glGetTexParameterIiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameterIivEXT(GLenum target, GLenum pname, GLint * params) {
    glad_glGetTexParameterIivEXT = (PFNGLGETTEXPARAMETERIIVEXTPROC) glad_gl_on_demand_loader("glGetTexParameterIivEXT");
    glad_glGetTexParameterIivEXT(target, pname, params);
}
PFNGLGETTEXPARAMETERIIVEXTPROC glad_glGetTexParameterIivEXT = glad_on_demand_impl_glGetTexParameterIivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params) {
    glad_glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC) glad_gl_on_demand_loader("glGetTexParameterIuiv");
    glad_glGetTexParameterIuiv(target, pname, params);
}
PFNGLGETTEXPARAMETERIUIVPROC glad_glGetTexParameterIuiv = glad_on_demand_impl_glGetTexParameterIuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameterIuivEXT(GLenum target, GLenum pname, GLuint * params) {
    glad_glGetTexParameterIuivEXT = (PFNGLGETTEXPARAMETERIUIVEXTPROC) glad_gl_on_demand_loader("glGetTexParameterIuivEXT");
    glad_glGetTexParameterIuivEXT(target, pname, params);
}
PFNGLGETTEXPARAMETERIUIVEXTPROC glad_glGetTexParameterIuivEXT = glad_on_demand_impl_glGetTexParameterIuivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) {
    glad_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) glad_gl_on_demand_loader("glGetTexParameterfv");
    glad_glGetTexParameterfv(target, pname, params);
}
PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv = glad_on_demand_impl_glGetTexParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTexParameteriv(GLenum target, GLenum pname, GLint * params) {
    glad_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) glad_gl_on_demand_loader("glGetTexParameteriv");
    glad_glGetTexParameteriv(target, pname, params);
}
PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv = glad_on_demand_impl_glGetTexParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glGetTextureImageEXT(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void * pixels) {
    glad_glGetTextureImageEXT = (PFNGLGETTEXTUREIMAGEEXTPROC) glad_gl_on_demand_loader("glGetTextureImageEXT");
    glad_glGetTextureImageEXT(texture, target, level, format, type, pixels);
}
PFNGLGETTEXTUREIMAGEEXTPROC glad_glGetTextureImageEXT = glad_on_demand_impl_glGetTextureImageEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTextureLevelParameterfvEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat * params) {
    glad_glGetTextureLevelParameterfvEXT = (PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC) glad_gl_on_demand_loader("glGetTextureLevelParameterfvEXT");
    glad_glGetTextureLevelParameterfvEXT(texture, target, level, pname, params);
}
PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC glad_glGetTextureLevelParameterfvEXT = glad_on_demand_impl_glGetTextureLevelParameterfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTextureLevelParameterivEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLint * params) {
    glad_glGetTextureLevelParameterivEXT = (PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetTextureLevelParameterivEXT");
    glad_glGetTextureLevelParameterivEXT(texture, target, level, pname, params);
}
PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC glad_glGetTextureLevelParameterivEXT = glad_on_demand_impl_glGetTextureLevelParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, GLint * params) {
    glad_glGetTextureParameterIivEXT = (PFNGLGETTEXTUREPARAMETERIIVEXTPROC) glad_gl_on_demand_loader("glGetTextureParameterIivEXT");
    glad_glGetTextureParameterIivEXT(texture, target, pname, params);
}
PFNGLGETTEXTUREPARAMETERIIVEXTPROC glad_glGetTextureParameterIivEXT = glad_on_demand_impl_glGetTextureParameterIivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, GLuint * params) {
    glad_glGetTextureParameterIuivEXT = (PFNGLGETTEXTUREPARAMETERIUIVEXTPROC) glad_gl_on_demand_loader("glGetTextureParameterIuivEXT");
    glad_glGetTextureParameterIuivEXT(texture, target, pname, params);
}
PFNGLGETTEXTUREPARAMETERIUIVEXTPROC glad_glGetTextureParameterIuivEXT = glad_on_demand_impl_glGetTextureParameterIuivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, GLfloat * params) {
    glad_glGetTextureParameterfvEXT = (PFNGLGETTEXTUREPARAMETERFVEXTPROC) glad_gl_on_demand_loader("glGetTextureParameterfvEXT");
    glad_glGetTextureParameterfvEXT(texture, target, pname, params);
}
PFNGLGETTEXTUREPARAMETERFVEXTPROC glad_glGetTextureParameterfvEXT = glad_on_demand_impl_glGetTextureParameterfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, GLint * params) {
    glad_glGetTextureParameterivEXT = (PFNGLGETTEXTUREPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glGetTextureParameterivEXT");
    glad_glGetTextureParameterivEXT(texture, target, pname, params);
}
PFNGLGETTEXTUREPARAMETERIVEXTPROC glad_glGetTextureParameterivEXT = glad_on_demand_impl_glGetTextureParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTrackMatrixivNV(GLenum target, GLuint address, GLenum pname, GLint * params) {
    glad_glGetTrackMatrixivNV = (PFNGLGETTRACKMATRIXIVNVPROC) glad_gl_on_demand_loader("glGetTrackMatrixivNV");
    glad_glGetTrackMatrixivNV(target, address, pname, params);
}
PFNGLGETTRACKMATRIXIVNVPROC glad_glGetTrackMatrixivNV = glad_on_demand_impl_glGetTrackMatrixivNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name) {
    glad_glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) glad_gl_on_demand_loader("glGetTransformFeedbackVarying");
    glad_glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_glGetTransformFeedbackVarying = glad_on_demand_impl_glGetTransformFeedbackVarying;
static void GLAD_API_PTR glad_on_demand_impl_glGetTransformFeedbackVaryingEXT(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name) {
    glad_glGetTransformFeedbackVaryingEXT = (PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC) glad_gl_on_demand_loader("glGetTransformFeedbackVaryingEXT");
    glad_glGetTransformFeedbackVaryingEXT(program, index, bufSize, length, size, type, name);
}
PFNGLGETTRANSFORMFEEDBACKVARYINGEXTPROC glad_glGetTransformFeedbackVaryingEXT = glad_on_demand_impl_glGetTransformFeedbackVaryingEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetTransformFeedbackVaryingNV(GLuint program, GLuint index, GLint * location) {
    glad_glGetTransformFeedbackVaryingNV = (PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC) glad_gl_on_demand_loader("glGetTransformFeedbackVaryingNV");
    glad_glGetTransformFeedbackVaryingNV(program, index, location);
}
PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC glad_glGetTransformFeedbackVaryingNV = glad_on_demand_impl_glGetTransformFeedbackVaryingNV;
static GLuint GLAD_API_PTR glad_on_demand_impl_glGetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName) {
    glad_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC) glad_gl_on_demand_loader("glGetUniformBlockIndex");
    return glad_glGetUniformBlockIndex(program, uniformBlockName);
}
PFNGLGETUNIFORMBLOCKINDEXPROC glad_glGetUniformBlockIndex = glad_on_demand_impl_glGetUniformBlockIndex;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices) {
    glad_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC) glad_gl_on_demand_loader("glGetUniformIndices");
    glad_glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
}
PFNGLGETUNIFORMINDICESPROC glad_glGetUniformIndices = glad_on_demand_impl_glGetUniformIndices;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetUniformLocation(GLuint program, const GLchar * name) {
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) glad_gl_on_demand_loader("glGetUniformLocation");
    return glad_glGetUniformLocation(program, name);
}
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = glad_on_demand_impl_glGetUniformLocation;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetUniformLocationARB(GLhandleARB programObj, const GLcharARB * name) {
    glad_glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) glad_gl_on_demand_loader("glGetUniformLocationARB");
    return glad_glGetUniformLocationARB(programObj, name);
}
PFNGLGETUNIFORMLOCATIONARBPROC glad_glGetUniformLocationARB = glad_on_demand_impl_glGetUniformLocationARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformfv(GLuint program, GLint location, GLfloat * params) {
    glad_glGetUniformfv = (PFNGLGETUNIFORMFVPROC) glad_gl_on_demand_loader("glGetUniformfv");
    glad_glGetUniformfv(program, location, params);
}
PFNGLGETUNIFORMFVPROC glad_glGetUniformfv = glad_on_demand_impl_glGetUniformfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformfvARB(GLhandleARB programObj, GLint location, GLfloat * params) {
    glad_glGetUniformfvARB = (PFNGLGETUNIFORMFVARBPROC) glad_gl_on_demand_loader("glGetUniformfvARB");
    glad_glGetUniformfvARB(programObj, location, params);
}
PFNGLGETUNIFORMFVARBPROC glad_glGetUniformfvARB = glad_on_demand_impl_glGetUniformfvARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformiv(GLuint program, GLint location, GLint * params) {
    glad_glGetUniformiv = (PFNGLGETUNIFORMIVPROC) glad_gl_on_demand_loader("glGetUniformiv");
    glad_glGetUniformiv(program, location, params);
}
PFNGLGETUNIFORMIVPROC glad_glGetUniformiv = glad_on_demand_impl_glGetUniformiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformivARB(GLhandleARB programObj, GLint location, GLint * params) {
    glad_glGetUniformivARB = (PFNGLGETUNIFORMIVARBPROC) glad_gl_on_demand_loader("glGetUniformivARB");
    glad_glGetUniformivARB(programObj, location, params);
}
PFNGLGETUNIFORMIVARBPROC glad_glGetUniformivARB = glad_on_demand_impl_glGetUniformivARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformuiv(GLuint program, GLint location, GLuint * params) {
    glad_glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC) glad_gl_on_demand_loader("glGetUniformuiv");
    glad_glGetUniformuiv(program, location, params);
}
PFNGLGETUNIFORMUIVPROC glad_glGetUniformuiv = glad_on_demand_impl_glGetUniformuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetUniformuivEXT(GLuint program, GLint location, GLuint * params) {
    glad_glGetUniformuivEXT = (PFNGLGETUNIFORMUIVEXTPROC) glad_gl_on_demand_loader("glGetUniformuivEXT");
    glad_glGetUniformuivEXT(program, location, params);
}
PFNGLGETUNIFORMUIVEXTPROC glad_glGetUniformuivEXT = glad_on_demand_impl_glGetUniformuivEXT;
static GLint GLAD_API_PTR glad_on_demand_impl_glGetVaryingLocationNV(GLuint program, const GLchar * name) {
    glad_glGetVaryingLocationNV = (PFNGLGETVARYINGLOCATIONNVPROC) glad_gl_on_demand_loader("glGetVaryingLocationNV");
    return glad_glGetVaryingLocationNV(program, name);
}
PFNGLGETVARYINGLOCATIONNVPROC glad_glGetVaryingLocationNV = glad_on_demand_impl_glGetVaryingLocationNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexArrayIntegeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, GLint * param) {
    glad_glGetVertexArrayIntegeri_vEXT = (PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC) glad_gl_on_demand_loader("glGetVertexArrayIntegeri_vEXT");
    glad_glGetVertexArrayIntegeri_vEXT(vaobj, index, pname, param);
}
PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC glad_glGetVertexArrayIntegeri_vEXT = glad_on_demand_impl_glGetVertexArrayIntegeri_vEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexArrayIntegervEXT(GLuint vaobj, GLenum pname, GLint * param) {
    glad_glGetVertexArrayIntegervEXT = (PFNGLGETVERTEXARRAYINTEGERVEXTPROC) glad_gl_on_demand_loader("glGetVertexArrayIntegervEXT");
    glad_glGetVertexArrayIntegervEXT(vaobj, pname, param);
}
PFNGLGETVERTEXARRAYINTEGERVEXTPROC glad_glGetVertexArrayIntegervEXT = glad_on_demand_impl_glGetVertexArrayIntegervEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexArrayPointeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, void ** param) {
    glad_glGetVertexArrayPointeri_vEXT = (PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC) glad_gl_on_demand_loader("glGetVertexArrayPointeri_vEXT");
    glad_glGetVertexArrayPointeri_vEXT(vaobj, index, pname, param);
}
PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC glad_glGetVertexArrayPointeri_vEXT = glad_on_demand_impl_glGetVertexArrayPointeri_vEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexArrayPointervEXT(GLuint vaobj, GLenum pname, void ** param) {
    glad_glGetVertexArrayPointervEXT = (PFNGLGETVERTEXARRAYPOINTERVEXTPROC) glad_gl_on_demand_loader("glGetVertexArrayPointervEXT");
    glad_glGetVertexArrayPointervEXT(vaobj, pname, param);
}
PFNGLGETVERTEXARRAYPOINTERVEXTPROC glad_glGetVertexArrayPointervEXT = glad_on_demand_impl_glGetVertexArrayPointervEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params) {
    glad_glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC) glad_gl_on_demand_loader("glGetVertexAttribIiv");
    glad_glGetVertexAttribIiv(index, pname, params);
}
PFNGLGETVERTEXATTRIBIIVPROC glad_glGetVertexAttribIiv = glad_on_demand_impl_glGetVertexAttribIiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribIivEXT(GLuint index, GLenum pname, GLint * params) {
    glad_glGetVertexAttribIivEXT = (PFNGLGETVERTEXATTRIBIIVEXTPROC) glad_gl_on_demand_loader("glGetVertexAttribIivEXT");
    glad_glGetVertexAttribIivEXT(index, pname, params);
}
PFNGLGETVERTEXATTRIBIIVEXTPROC glad_glGetVertexAttribIivEXT = glad_on_demand_impl_glGetVertexAttribIivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params) {
    glad_glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC) glad_gl_on_demand_loader("glGetVertexAttribIuiv");
    glad_glGetVertexAttribIuiv(index, pname, params);
}
PFNGLGETVERTEXATTRIBIUIVPROC glad_glGetVertexAttribIuiv = glad_on_demand_impl_glGetVertexAttribIuiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribIuivEXT(GLuint index, GLenum pname, GLuint * params) {
    glad_glGetVertexAttribIuivEXT = (PFNGLGETVERTEXATTRIBIUIVEXTPROC) glad_gl_on_demand_loader("glGetVertexAttribIuivEXT");
    glad_glGetVertexAttribIuivEXT(index, pname, params);
}
PFNGLGETVERTEXATTRIBIUIVEXTPROC glad_glGetVertexAttribIuivEXT = glad_on_demand_impl_glGetVertexAttribIuivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer) {
    glad_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) glad_gl_on_demand_loader("glGetVertexAttribPointerv");
    glad_glGetVertexAttribPointerv(index, pname, pointer);
}
PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv = glad_on_demand_impl_glGetVertexAttribPointerv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribPointervARB(GLuint index, GLenum pname, void ** pointer) {
    glad_glGetVertexAttribPointervARB = (PFNGLGETVERTEXATTRIBPOINTERVARBPROC) glad_gl_on_demand_loader("glGetVertexAttribPointervARB");
    glad_glGetVertexAttribPointervARB(index, pname, pointer);
}
PFNGLGETVERTEXATTRIBPOINTERVARBPROC glad_glGetVertexAttribPointervARB = glad_on_demand_impl_glGetVertexAttribPointervARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribPointervNV(GLuint index, GLenum pname, void ** pointer) {
    glad_glGetVertexAttribPointervNV = (PFNGLGETVERTEXATTRIBPOINTERVNVPROC) glad_gl_on_demand_loader("glGetVertexAttribPointervNV");
    glad_glGetVertexAttribPointervNV(index, pname, pointer);
}
PFNGLGETVERTEXATTRIBPOINTERVNVPROC glad_glGetVertexAttribPointervNV = glad_on_demand_impl_glGetVertexAttribPointervNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params) {
    glad_glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC) glad_gl_on_demand_loader("glGetVertexAttribdv");
    glad_glGetVertexAttribdv(index, pname, params);
}
PFNGLGETVERTEXATTRIBDVPROC glad_glGetVertexAttribdv = glad_on_demand_impl_glGetVertexAttribdv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribdvARB(GLuint index, GLenum pname, GLdouble * params) {
    glad_glGetVertexAttribdvARB = (PFNGLGETVERTEXATTRIBDVARBPROC) glad_gl_on_demand_loader("glGetVertexAttribdvARB");
    glad_glGetVertexAttribdvARB(index, pname, params);
}
PFNGLGETVERTEXATTRIBDVARBPROC glad_glGetVertexAttribdvARB = glad_on_demand_impl_glGetVertexAttribdvARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribdvNV(GLuint index, GLenum pname, GLdouble * params) {
    glad_glGetVertexAttribdvNV = (PFNGLGETVERTEXATTRIBDVNVPROC) glad_gl_on_demand_loader("glGetVertexAttribdvNV");
    glad_glGetVertexAttribdvNV(index, pname, params);
}
PFNGLGETVERTEXATTRIBDVNVPROC glad_glGetVertexAttribdvNV = glad_on_demand_impl_glGetVertexAttribdvNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params) {
    glad_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC) glad_gl_on_demand_loader("glGetVertexAttribfv");
    glad_glGetVertexAttribfv(index, pname, params);
}
PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv = glad_on_demand_impl_glGetVertexAttribfv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribfvARB(GLuint index, GLenum pname, GLfloat * params) {
    glad_glGetVertexAttribfvARB = (PFNGLGETVERTEXATTRIBFVARBPROC) glad_gl_on_demand_loader("glGetVertexAttribfvARB");
    glad_glGetVertexAttribfvARB(index, pname, params);
}
PFNGLGETVERTEXATTRIBFVARBPROC glad_glGetVertexAttribfvARB = glad_on_demand_impl_glGetVertexAttribfvARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribfvNV(GLuint index, GLenum pname, GLfloat * params) {
    glad_glGetVertexAttribfvNV = (PFNGLGETVERTEXATTRIBFVNVPROC) glad_gl_on_demand_loader("glGetVertexAttribfvNV");
    glad_glGetVertexAttribfvNV(index, pname, params);
}
PFNGLGETVERTEXATTRIBFVNVPROC glad_glGetVertexAttribfvNV = glad_on_demand_impl_glGetVertexAttribfvNV;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribiv(GLuint index, GLenum pname, GLint * params) {
    glad_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC) glad_gl_on_demand_loader("glGetVertexAttribiv");
    glad_glGetVertexAttribiv(index, pname, params);
}
PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv = glad_on_demand_impl_glGetVertexAttribiv;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribivARB(GLuint index, GLenum pname, GLint * params) {
    glad_glGetVertexAttribivARB = (PFNGLGETVERTEXATTRIBIVARBPROC) glad_gl_on_demand_loader("glGetVertexAttribivARB");
    glad_glGetVertexAttribivARB(index, pname, params);
}
PFNGLGETVERTEXATTRIBIVARBPROC glad_glGetVertexAttribivARB = glad_on_demand_impl_glGetVertexAttribivARB;
static void GLAD_API_PTR glad_on_demand_impl_glGetVertexAttribivNV(GLuint index, GLenum pname, GLint * params) {
    glad_glGetVertexAttribivNV = (PFNGLGETVERTEXATTRIBIVNVPROC) glad_gl_on_demand_loader("glGetVertexAttribivNV");
    glad_glGetVertexAttribivNV(index, pname, params);
}
PFNGLGETVERTEXATTRIBIVNVPROC glad_glGetVertexAttribivNV = glad_on_demand_impl_glGetVertexAttribivNV;
static void GLAD_API_PTR glad_on_demand_impl_glHint(GLenum target, GLenum mode) {
    glad_glHint = (PFNGLHINTPROC) glad_gl_on_demand_loader("glHint");
    glad_glHint(target, mode);
}
PFNGLHINTPROC glad_glHint = glad_on_demand_impl_glHint;
static void GLAD_API_PTR glad_on_demand_impl_glIndexPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void * pointer) {
    glad_glIndexPointerEXT = (PFNGLINDEXPOINTEREXTPROC) glad_gl_on_demand_loader("glIndexPointerEXT");
    glad_glIndexPointerEXT(type, stride, count, pointer);
}
PFNGLINDEXPOINTEREXTPROC glad_glIndexPointerEXT = glad_on_demand_impl_glIndexPointerEXT;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsBuffer(GLuint buffer) {
    glad_glIsBuffer = (PFNGLISBUFFERPROC) glad_gl_on_demand_loader("glIsBuffer");
    return glad_glIsBuffer(buffer);
}
PFNGLISBUFFERPROC glad_glIsBuffer = glad_on_demand_impl_glIsBuffer;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsBufferARB(GLuint buffer) {
    glad_glIsBufferARB = (PFNGLISBUFFERARBPROC) glad_gl_on_demand_loader("glIsBufferARB");
    return glad_glIsBufferARB(buffer);
}
PFNGLISBUFFERARBPROC glad_glIsBufferARB = glad_on_demand_impl_glIsBufferARB;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsEnabled(GLenum cap) {
    glad_glIsEnabled = (PFNGLISENABLEDPROC) glad_gl_on_demand_loader("glIsEnabled");
    return glad_glIsEnabled(cap);
}
PFNGLISENABLEDPROC glad_glIsEnabled = glad_on_demand_impl_glIsEnabled;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsEnabledIndexedEXT(GLenum target, GLuint index) {
    glad_glIsEnabledIndexedEXT = (PFNGLISENABLEDINDEXEDEXTPROC) glad_gl_on_demand_loader("glIsEnabledIndexedEXT");
    return glad_glIsEnabledIndexedEXT(target, index);
}
PFNGLISENABLEDINDEXEDEXTPROC glad_glIsEnabledIndexedEXT = glad_on_demand_impl_glIsEnabledIndexedEXT;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsEnabledi(GLenum target, GLuint index) {
    glad_glIsEnabledi = (PFNGLISENABLEDIPROC) glad_gl_on_demand_loader("glIsEnabledi");
    return glad_glIsEnabledi(target, index);
}
PFNGLISENABLEDIPROC glad_glIsEnabledi = glad_on_demand_impl_glIsEnabledi;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsFramebuffer(GLuint framebuffer) {
    glad_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) glad_gl_on_demand_loader("glIsFramebuffer");
    return glad_glIsFramebuffer(framebuffer);
}
PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer = glad_on_demand_impl_glIsFramebuffer;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsFramebufferEXT(GLuint framebuffer) {
    glad_glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC) glad_gl_on_demand_loader("glIsFramebufferEXT");
    return glad_glIsFramebufferEXT(framebuffer);
}
PFNGLISFRAMEBUFFEREXTPROC glad_glIsFramebufferEXT = glad_on_demand_impl_glIsFramebufferEXT;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsProgram(GLuint program) {
    glad_glIsProgram = (PFNGLISPROGRAMPROC) glad_gl_on_demand_loader("glIsProgram");
    return glad_glIsProgram(program);
}
PFNGLISPROGRAMPROC glad_glIsProgram = glad_on_demand_impl_glIsProgram;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsProgramARB(GLuint program) {
    glad_glIsProgramARB = (PFNGLISPROGRAMARBPROC) glad_gl_on_demand_loader("glIsProgramARB");
    return glad_glIsProgramARB(program);
}
PFNGLISPROGRAMARBPROC glad_glIsProgramARB = glad_on_demand_impl_glIsProgramARB;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsProgramNV(GLuint id) {
    glad_glIsProgramNV = (PFNGLISPROGRAMNVPROC) glad_gl_on_demand_loader("glIsProgramNV");
    return glad_glIsProgramNV(id);
}
PFNGLISPROGRAMNVPROC glad_glIsProgramNV = glad_on_demand_impl_glIsProgramNV;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsQuery(GLuint id) {
    glad_glIsQuery = (PFNGLISQUERYPROC) glad_gl_on_demand_loader("glIsQuery");
    return glad_glIsQuery(id);
}
PFNGLISQUERYPROC glad_glIsQuery = glad_on_demand_impl_glIsQuery;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsQueryARB(GLuint id) {
    glad_glIsQueryARB = (PFNGLISQUERYARBPROC) glad_gl_on_demand_loader("glIsQueryARB");
    return glad_glIsQueryARB(id);
}
PFNGLISQUERYARBPROC glad_glIsQueryARB = glad_on_demand_impl_glIsQueryARB;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsRenderbuffer(GLuint renderbuffer) {
    glad_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) glad_gl_on_demand_loader("glIsRenderbuffer");
    return glad_glIsRenderbuffer(renderbuffer);
}
PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer = glad_on_demand_impl_glIsRenderbuffer;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsRenderbufferEXT(GLuint renderbuffer) {
    glad_glIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXTPROC) glad_gl_on_demand_loader("glIsRenderbufferEXT");
    return glad_glIsRenderbufferEXT(renderbuffer);
}
PFNGLISRENDERBUFFEREXTPROC glad_glIsRenderbufferEXT = glad_on_demand_impl_glIsRenderbufferEXT;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsSampler(GLuint sampler) {
    glad_glIsSampler = (PFNGLISSAMPLERPROC) glad_gl_on_demand_loader("glIsSampler");
    return glad_glIsSampler(sampler);
}
PFNGLISSAMPLERPROC glad_glIsSampler = glad_on_demand_impl_glIsSampler;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsShader(GLuint shader) {
    glad_glIsShader = (PFNGLISSHADERPROC) glad_gl_on_demand_loader("glIsShader");
    return glad_glIsShader(shader);
}
PFNGLISSHADERPROC glad_glIsShader = glad_on_demand_impl_glIsShader;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsSync(GLsync sync) {
    glad_glIsSync = (PFNGLISSYNCPROC) glad_gl_on_demand_loader("glIsSync");
    return glad_glIsSync(sync);
}
PFNGLISSYNCPROC glad_glIsSync = glad_on_demand_impl_glIsSync;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsTexture(GLuint texture) {
    glad_glIsTexture = (PFNGLISTEXTUREPROC) glad_gl_on_demand_loader("glIsTexture");
    return glad_glIsTexture(texture);
}
PFNGLISTEXTUREPROC glad_glIsTexture = glad_on_demand_impl_glIsTexture;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsTextureEXT(GLuint texture) {
    glad_glIsTextureEXT = (PFNGLISTEXTUREEXTPROC) glad_gl_on_demand_loader("glIsTextureEXT");
    return glad_glIsTextureEXT(texture);
}
PFNGLISTEXTUREEXTPROC glad_glIsTextureEXT = glad_on_demand_impl_glIsTextureEXT;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsVertexArray(GLuint array) {
    glad_glIsVertexArray = (PFNGLISVERTEXARRAYPROC) glad_gl_on_demand_loader("glIsVertexArray");
    return glad_glIsVertexArray(array);
}
PFNGLISVERTEXARRAYPROC glad_glIsVertexArray = glad_on_demand_impl_glIsVertexArray;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glIsVertexArrayAPPLE(GLuint array) {
    glad_glIsVertexArrayAPPLE = (PFNGLISVERTEXARRAYAPPLEPROC) glad_gl_on_demand_loader("glIsVertexArrayAPPLE");
    return glad_glIsVertexArrayAPPLE(array);
}
PFNGLISVERTEXARRAYAPPLEPROC glad_glIsVertexArrayAPPLE = glad_on_demand_impl_glIsVertexArrayAPPLE;
static void GLAD_API_PTR glad_on_demand_impl_glLineWidth(GLfloat width) {
    glad_glLineWidth = (PFNGLLINEWIDTHPROC) glad_gl_on_demand_loader("glLineWidth");
    glad_glLineWidth(width);
}
PFNGLLINEWIDTHPROC glad_glLineWidth = glad_on_demand_impl_glLineWidth;
static void GLAD_API_PTR glad_on_demand_impl_glLinkProgram(GLuint program) {
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC) glad_gl_on_demand_loader("glLinkProgram");
    glad_glLinkProgram(program);
}
PFNGLLINKPROGRAMPROC glad_glLinkProgram = glad_on_demand_impl_glLinkProgram;
static void GLAD_API_PTR glad_on_demand_impl_glLinkProgramARB(GLhandleARB programObj) {
    glad_glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) glad_gl_on_demand_loader("glLinkProgramARB");
    glad_glLinkProgramARB(programObj);
}
PFNGLLINKPROGRAMARBPROC glad_glLinkProgramARB = glad_on_demand_impl_glLinkProgramARB;
static void GLAD_API_PTR glad_on_demand_impl_glLoadProgramNV(GLenum target, GLuint id, GLsizei len, const GLubyte * program) {
    glad_glLoadProgramNV = (PFNGLLOADPROGRAMNVPROC) glad_gl_on_demand_loader("glLoadProgramNV");
    glad_glLoadProgramNV(target, id, len, program);
}
PFNGLLOADPROGRAMNVPROC glad_glLoadProgramNV = glad_on_demand_impl_glLoadProgramNV;
static void GLAD_API_PTR glad_on_demand_impl_glLogicOp(GLenum opcode) {
    glad_glLogicOp = (PFNGLLOGICOPPROC) glad_gl_on_demand_loader("glLogicOp");
    glad_glLogicOp(opcode);
}
PFNGLLOGICOPPROC glad_glLogicOp = glad_on_demand_impl_glLogicOp;
static void * GLAD_API_PTR glad_on_demand_impl_glMapBuffer(GLenum target, GLenum access) {
    glad_glMapBuffer = (PFNGLMAPBUFFERPROC) glad_gl_on_demand_loader("glMapBuffer");
    return glad_glMapBuffer(target, access);
}
PFNGLMAPBUFFERPROC glad_glMapBuffer = glad_on_demand_impl_glMapBuffer;
static void * GLAD_API_PTR glad_on_demand_impl_glMapBufferARB(GLenum target, GLenum access) {
    glad_glMapBufferARB = (PFNGLMAPBUFFERARBPROC) glad_gl_on_demand_loader("glMapBufferARB");
    return glad_glMapBufferARB(target, access);
}
PFNGLMAPBUFFERARBPROC glad_glMapBufferARB = glad_on_demand_impl_glMapBufferARB;
static void * GLAD_API_PTR glad_on_demand_impl_glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {
    glad_glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC) glad_gl_on_demand_loader("glMapBufferRange");
    return glad_glMapBufferRange(target, offset, length, access);
}
PFNGLMAPBUFFERRANGEPROC glad_glMapBufferRange = glad_on_demand_impl_glMapBufferRange;
static void * GLAD_API_PTR glad_on_demand_impl_glMapNamedBufferEXT(GLuint buffer, GLenum access) {
    glad_glMapNamedBufferEXT = (PFNGLMAPNAMEDBUFFEREXTPROC) glad_gl_on_demand_loader("glMapNamedBufferEXT");
    return glad_glMapNamedBufferEXT(buffer, access);
}
PFNGLMAPNAMEDBUFFEREXTPROC glad_glMapNamedBufferEXT = glad_on_demand_impl_glMapNamedBufferEXT;
static void * GLAD_API_PTR glad_on_demand_impl_glMapNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) {
    glad_glMapNamedBufferRangeEXT = (PFNGLMAPNAMEDBUFFERRANGEEXTPROC) glad_gl_on_demand_loader("glMapNamedBufferRangeEXT");
    return glad_glMapNamedBufferRangeEXT(buffer, offset, length, access);
}
PFNGLMAPNAMEDBUFFERRANGEEXTPROC glad_glMapNamedBufferRangeEXT = glad_on_demand_impl_glMapNamedBufferRangeEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixFrustumEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
    glad_glMatrixFrustumEXT = (PFNGLMATRIXFRUSTUMEXTPROC) glad_gl_on_demand_loader("glMatrixFrustumEXT");
    glad_glMatrixFrustumEXT(mode, left, right, bottom, top, zNear, zFar);
}
PFNGLMATRIXFRUSTUMEXTPROC glad_glMatrixFrustumEXT = glad_on_demand_impl_glMatrixFrustumEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixLoadIdentityEXT(GLenum mode) {
    glad_glMatrixLoadIdentityEXT = (PFNGLMATRIXLOADIDENTITYEXTPROC) glad_gl_on_demand_loader("glMatrixLoadIdentityEXT");
    glad_glMatrixLoadIdentityEXT(mode);
}
PFNGLMATRIXLOADIDENTITYEXTPROC glad_glMatrixLoadIdentityEXT = glad_on_demand_impl_glMatrixLoadIdentityEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixLoadTransposedEXT(GLenum mode, const GLdouble * m) {
    glad_glMatrixLoadTransposedEXT = (PFNGLMATRIXLOADTRANSPOSEDEXTPROC) glad_gl_on_demand_loader("glMatrixLoadTransposedEXT");
    glad_glMatrixLoadTransposedEXT(mode, m);
}
PFNGLMATRIXLOADTRANSPOSEDEXTPROC glad_glMatrixLoadTransposedEXT = glad_on_demand_impl_glMatrixLoadTransposedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixLoadTransposefEXT(GLenum mode, const GLfloat * m) {
    glad_glMatrixLoadTransposefEXT = (PFNGLMATRIXLOADTRANSPOSEFEXTPROC) glad_gl_on_demand_loader("glMatrixLoadTransposefEXT");
    glad_glMatrixLoadTransposefEXT(mode, m);
}
PFNGLMATRIXLOADTRANSPOSEFEXTPROC glad_glMatrixLoadTransposefEXT = glad_on_demand_impl_glMatrixLoadTransposefEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixLoaddEXT(GLenum mode, const GLdouble * m) {
    glad_glMatrixLoaddEXT = (PFNGLMATRIXLOADDEXTPROC) glad_gl_on_demand_loader("glMatrixLoaddEXT");
    glad_glMatrixLoaddEXT(mode, m);
}
PFNGLMATRIXLOADDEXTPROC glad_glMatrixLoaddEXT = glad_on_demand_impl_glMatrixLoaddEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixLoadfEXT(GLenum mode, const GLfloat * m) {
    glad_glMatrixLoadfEXT = (PFNGLMATRIXLOADFEXTPROC) glad_gl_on_demand_loader("glMatrixLoadfEXT");
    glad_glMatrixLoadfEXT(mode, m);
}
PFNGLMATRIXLOADFEXTPROC glad_glMatrixLoadfEXT = glad_on_demand_impl_glMatrixLoadfEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixMultTransposedEXT(GLenum mode, const GLdouble * m) {
    glad_glMatrixMultTransposedEXT = (PFNGLMATRIXMULTTRANSPOSEDEXTPROC) glad_gl_on_demand_loader("glMatrixMultTransposedEXT");
    glad_glMatrixMultTransposedEXT(mode, m);
}
PFNGLMATRIXMULTTRANSPOSEDEXTPROC glad_glMatrixMultTransposedEXT = glad_on_demand_impl_glMatrixMultTransposedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixMultTransposefEXT(GLenum mode, const GLfloat * m) {
    glad_glMatrixMultTransposefEXT = (PFNGLMATRIXMULTTRANSPOSEFEXTPROC) glad_gl_on_demand_loader("glMatrixMultTransposefEXT");
    glad_glMatrixMultTransposefEXT(mode, m);
}
PFNGLMATRIXMULTTRANSPOSEFEXTPROC glad_glMatrixMultTransposefEXT = glad_on_demand_impl_glMatrixMultTransposefEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixMultdEXT(GLenum mode, const GLdouble * m) {
    glad_glMatrixMultdEXT = (PFNGLMATRIXMULTDEXTPROC) glad_gl_on_demand_loader("glMatrixMultdEXT");
    glad_glMatrixMultdEXT(mode, m);
}
PFNGLMATRIXMULTDEXTPROC glad_glMatrixMultdEXT = glad_on_demand_impl_glMatrixMultdEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixMultfEXT(GLenum mode, const GLfloat * m) {
    glad_glMatrixMultfEXT = (PFNGLMATRIXMULTFEXTPROC) glad_gl_on_demand_loader("glMatrixMultfEXT");
    glad_glMatrixMultfEXT(mode, m);
}
PFNGLMATRIXMULTFEXTPROC glad_glMatrixMultfEXT = glad_on_demand_impl_glMatrixMultfEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixOrthoEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
    glad_glMatrixOrthoEXT = (PFNGLMATRIXORTHOEXTPROC) glad_gl_on_demand_loader("glMatrixOrthoEXT");
    glad_glMatrixOrthoEXT(mode, left, right, bottom, top, zNear, zFar);
}
PFNGLMATRIXORTHOEXTPROC glad_glMatrixOrthoEXT = glad_on_demand_impl_glMatrixOrthoEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixPopEXT(GLenum mode) {
    glad_glMatrixPopEXT = (PFNGLMATRIXPOPEXTPROC) glad_gl_on_demand_loader("glMatrixPopEXT");
    glad_glMatrixPopEXT(mode);
}
PFNGLMATRIXPOPEXTPROC glad_glMatrixPopEXT = glad_on_demand_impl_glMatrixPopEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixPushEXT(GLenum mode) {
    glad_glMatrixPushEXT = (PFNGLMATRIXPUSHEXTPROC) glad_gl_on_demand_loader("glMatrixPushEXT");
    glad_glMatrixPushEXT(mode);
}
PFNGLMATRIXPUSHEXTPROC glad_glMatrixPushEXT = glad_on_demand_impl_glMatrixPushEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixRotatedEXT(GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
    glad_glMatrixRotatedEXT = (PFNGLMATRIXROTATEDEXTPROC) glad_gl_on_demand_loader("glMatrixRotatedEXT");
    glad_glMatrixRotatedEXT(mode, angle, x, y, z);
}
PFNGLMATRIXROTATEDEXTPROC glad_glMatrixRotatedEXT = glad_on_demand_impl_glMatrixRotatedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixRotatefEXT(GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    glad_glMatrixRotatefEXT = (PFNGLMATRIXROTATEFEXTPROC) glad_gl_on_demand_loader("glMatrixRotatefEXT");
    glad_glMatrixRotatefEXT(mode, angle, x, y, z);
}
PFNGLMATRIXROTATEFEXTPROC glad_glMatrixRotatefEXT = glad_on_demand_impl_glMatrixRotatefEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixScaledEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z) {
    glad_glMatrixScaledEXT = (PFNGLMATRIXSCALEDEXTPROC) glad_gl_on_demand_loader("glMatrixScaledEXT");
    glad_glMatrixScaledEXT(mode, x, y, z);
}
PFNGLMATRIXSCALEDEXTPROC glad_glMatrixScaledEXT = glad_on_demand_impl_glMatrixScaledEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixScalefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z) {
    glad_glMatrixScalefEXT = (PFNGLMATRIXSCALEFEXTPROC) glad_gl_on_demand_loader("glMatrixScalefEXT");
    glad_glMatrixScalefEXT(mode, x, y, z);
}
PFNGLMATRIXSCALEFEXTPROC glad_glMatrixScalefEXT = glad_on_demand_impl_glMatrixScalefEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixTranslatedEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z) {
    glad_glMatrixTranslatedEXT = (PFNGLMATRIXTRANSLATEDEXTPROC) glad_gl_on_demand_loader("glMatrixTranslatedEXT");
    glad_glMatrixTranslatedEXT(mode, x, y, z);
}
PFNGLMATRIXTRANSLATEDEXTPROC glad_glMatrixTranslatedEXT = glad_on_demand_impl_glMatrixTranslatedEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMatrixTranslatefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z) {
    glad_glMatrixTranslatefEXT = (PFNGLMATRIXTRANSLATEFEXTPROC) glad_gl_on_demand_loader("glMatrixTranslatefEXT");
    glad_glMatrixTranslatefEXT(mode, x, y, z);
}
PFNGLMATRIXTRANSLATEFEXTPROC glad_glMatrixTranslatefEXT = glad_on_demand_impl_glMatrixTranslatefEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount) {
    glad_glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC) glad_gl_on_demand_loader("glMultiDrawArrays");
    glad_glMultiDrawArrays(mode, first, count, drawcount);
}
PFNGLMULTIDRAWARRAYSPROC glad_glMultiDrawArrays = glad_on_demand_impl_glMultiDrawArrays;
static void GLAD_API_PTR glad_on_demand_impl_glMultiDrawArraysEXT(GLenum mode, const GLint * first, const GLsizei * count, GLsizei primcount) {
    glad_glMultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC) glad_gl_on_demand_loader("glMultiDrawArraysEXT");
    glad_glMultiDrawArraysEXT(mode, first, count, primcount);
}
PFNGLMULTIDRAWARRAYSEXTPROC glad_glMultiDrawArraysEXT = glad_on_demand_impl_glMultiDrawArraysEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount) {
    glad_glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) glad_gl_on_demand_loader("glMultiDrawElements");
    glad_glMultiDrawElements(mode, count, type, indices, drawcount);
}
PFNGLMULTIDRAWELEMENTSPROC glad_glMultiDrawElements = glad_on_demand_impl_glMultiDrawElements;
static void GLAD_API_PTR glad_on_demand_impl_glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex) {
    glad_glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) glad_gl_on_demand_loader("glMultiDrawElementsBaseVertex");
    glad_glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
}
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glad_glMultiDrawElementsBaseVertex = glad_on_demand_impl_glMultiDrawElementsBaseVertex;
static void GLAD_API_PTR glad_on_demand_impl_glMultiDrawElementsEXT(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei primcount) {
    glad_glMultiDrawElementsEXT = (PFNGLMULTIDRAWELEMENTSEXTPROC) glad_gl_on_demand_loader("glMultiDrawElementsEXT");
    glad_glMultiDrawElementsEXT(mode, count, type, indices, primcount);
}
PFNGLMULTIDRAWELEMENTSEXTPROC glad_glMultiDrawElementsEXT = glad_on_demand_impl_glMultiDrawElementsEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexBufferEXT(GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer) {
    glad_glMultiTexBufferEXT = (PFNGLMULTITEXBUFFEREXTPROC) glad_gl_on_demand_loader("glMultiTexBufferEXT");
    glad_glMultiTexBufferEXT(texunit, target, internalformat, buffer);
}
PFNGLMULTITEXBUFFEREXTPROC glad_glMultiTexBufferEXT = glad_on_demand_impl_glMultiTexBufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1dARB(GLenum target, GLdouble s) {
    glad_glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DARBPROC) glad_gl_on_demand_loader("glMultiTexCoord1dARB");
    glad_glMultiTexCoord1dARB(target, s);
}
PFNGLMULTITEXCOORD1DARBPROC glad_glMultiTexCoord1dARB = glad_on_demand_impl_glMultiTexCoord1dARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1dvARB(GLenum target, const GLdouble * v) {
    glad_glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord1dvARB");
    glad_glMultiTexCoord1dvARB(target, v);
}
PFNGLMULTITEXCOORD1DVARBPROC glad_glMultiTexCoord1dvARB = glad_on_demand_impl_glMultiTexCoord1dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1fARB(GLenum target, GLfloat s) {
    glad_glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC) glad_gl_on_demand_loader("glMultiTexCoord1fARB");
    glad_glMultiTexCoord1fARB(target, s);
}
PFNGLMULTITEXCOORD1FARBPROC glad_glMultiTexCoord1fARB = glad_on_demand_impl_glMultiTexCoord1fARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1fvARB(GLenum target, const GLfloat * v) {
    glad_glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord1fvARB");
    glad_glMultiTexCoord1fvARB(target, v);
}
PFNGLMULTITEXCOORD1FVARBPROC glad_glMultiTexCoord1fvARB = glad_on_demand_impl_glMultiTexCoord1fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1iARB(GLenum target, GLint s) {
    glad_glMultiTexCoord1iARB = (PFNGLMULTITEXCOORD1IARBPROC) glad_gl_on_demand_loader("glMultiTexCoord1iARB");
    glad_glMultiTexCoord1iARB(target, s);
}
PFNGLMULTITEXCOORD1IARBPROC glad_glMultiTexCoord1iARB = glad_on_demand_impl_glMultiTexCoord1iARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1ivARB(GLenum target, const GLint * v) {
    glad_glMultiTexCoord1ivARB = (PFNGLMULTITEXCOORD1IVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord1ivARB");
    glad_glMultiTexCoord1ivARB(target, v);
}
PFNGLMULTITEXCOORD1IVARBPROC glad_glMultiTexCoord1ivARB = glad_on_demand_impl_glMultiTexCoord1ivARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1sARB(GLenum target, GLshort s) {
    glad_glMultiTexCoord1sARB = (PFNGLMULTITEXCOORD1SARBPROC) glad_gl_on_demand_loader("glMultiTexCoord1sARB");
    glad_glMultiTexCoord1sARB(target, s);
}
PFNGLMULTITEXCOORD1SARBPROC glad_glMultiTexCoord1sARB = glad_on_demand_impl_glMultiTexCoord1sARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord1svARB(GLenum target, const GLshort * v) {
    glad_glMultiTexCoord1svARB = (PFNGLMULTITEXCOORD1SVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord1svARB");
    glad_glMultiTexCoord1svARB(target, v);
}
PFNGLMULTITEXCOORD1SVARBPROC glad_glMultiTexCoord1svARB = glad_on_demand_impl_glMultiTexCoord1svARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2dARB(GLenum target, GLdouble s, GLdouble t) {
    glad_glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DARBPROC) glad_gl_on_demand_loader("glMultiTexCoord2dARB");
    glad_glMultiTexCoord2dARB(target, s, t);
}
PFNGLMULTITEXCOORD2DARBPROC glad_glMultiTexCoord2dARB = glad_on_demand_impl_glMultiTexCoord2dARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2dvARB(GLenum target, const GLdouble * v) {
    glad_glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord2dvARB");
    glad_glMultiTexCoord2dvARB(target, v);
}
PFNGLMULTITEXCOORD2DVARBPROC glad_glMultiTexCoord2dvARB = glad_on_demand_impl_glMultiTexCoord2dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t) {
    glad_glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) glad_gl_on_demand_loader("glMultiTexCoord2fARB");
    glad_glMultiTexCoord2fARB(target, s, t);
}
PFNGLMULTITEXCOORD2FARBPROC glad_glMultiTexCoord2fARB = glad_on_demand_impl_glMultiTexCoord2fARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2fvARB(GLenum target, const GLfloat * v) {
    glad_glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord2fvARB");
    glad_glMultiTexCoord2fvARB(target, v);
}
PFNGLMULTITEXCOORD2FVARBPROC glad_glMultiTexCoord2fvARB = glad_on_demand_impl_glMultiTexCoord2fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2iARB(GLenum target, GLint s, GLint t) {
    glad_glMultiTexCoord2iARB = (PFNGLMULTITEXCOORD2IARBPROC) glad_gl_on_demand_loader("glMultiTexCoord2iARB");
    glad_glMultiTexCoord2iARB(target, s, t);
}
PFNGLMULTITEXCOORD2IARBPROC glad_glMultiTexCoord2iARB = glad_on_demand_impl_glMultiTexCoord2iARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2ivARB(GLenum target, const GLint * v) {
    glad_glMultiTexCoord2ivARB = (PFNGLMULTITEXCOORD2IVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord2ivARB");
    glad_glMultiTexCoord2ivARB(target, v);
}
PFNGLMULTITEXCOORD2IVARBPROC glad_glMultiTexCoord2ivARB = glad_on_demand_impl_glMultiTexCoord2ivARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2sARB(GLenum target, GLshort s, GLshort t) {
    glad_glMultiTexCoord2sARB = (PFNGLMULTITEXCOORD2SARBPROC) glad_gl_on_demand_loader("glMultiTexCoord2sARB");
    glad_glMultiTexCoord2sARB(target, s, t);
}
PFNGLMULTITEXCOORD2SARBPROC glad_glMultiTexCoord2sARB = glad_on_demand_impl_glMultiTexCoord2sARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord2svARB(GLenum target, const GLshort * v) {
    glad_glMultiTexCoord2svARB = (PFNGLMULTITEXCOORD2SVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord2svARB");
    glad_glMultiTexCoord2svARB(target, v);
}
PFNGLMULTITEXCOORD2SVARBPROC glad_glMultiTexCoord2svARB = glad_on_demand_impl_glMultiTexCoord2svARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r) {
    glad_glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DARBPROC) glad_gl_on_demand_loader("glMultiTexCoord3dARB");
    glad_glMultiTexCoord3dARB(target, s, t, r);
}
PFNGLMULTITEXCOORD3DARBPROC glad_glMultiTexCoord3dARB = glad_on_demand_impl_glMultiTexCoord3dARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3dvARB(GLenum target, const GLdouble * v) {
    glad_glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord3dvARB");
    glad_glMultiTexCoord3dvARB(target, v);
}
PFNGLMULTITEXCOORD3DVARBPROC glad_glMultiTexCoord3dvARB = glad_on_demand_impl_glMultiTexCoord3dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r) {
    glad_glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC) glad_gl_on_demand_loader("glMultiTexCoord3fARB");
    glad_glMultiTexCoord3fARB(target, s, t, r);
}
PFNGLMULTITEXCOORD3FARBPROC glad_glMultiTexCoord3fARB = glad_on_demand_impl_glMultiTexCoord3fARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3fvARB(GLenum target, const GLfloat * v) {
    glad_glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord3fvARB");
    glad_glMultiTexCoord3fvARB(target, v);
}
PFNGLMULTITEXCOORD3FVARBPROC glad_glMultiTexCoord3fvARB = glad_on_demand_impl_glMultiTexCoord3fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3iARB(GLenum target, GLint s, GLint t, GLint r) {
    glad_glMultiTexCoord3iARB = (PFNGLMULTITEXCOORD3IARBPROC) glad_gl_on_demand_loader("glMultiTexCoord3iARB");
    glad_glMultiTexCoord3iARB(target, s, t, r);
}
PFNGLMULTITEXCOORD3IARBPROC glad_glMultiTexCoord3iARB = glad_on_demand_impl_glMultiTexCoord3iARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3ivARB(GLenum target, const GLint * v) {
    glad_glMultiTexCoord3ivARB = (PFNGLMULTITEXCOORD3IVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord3ivARB");
    glad_glMultiTexCoord3ivARB(target, v);
}
PFNGLMULTITEXCOORD3IVARBPROC glad_glMultiTexCoord3ivARB = glad_on_demand_impl_glMultiTexCoord3ivARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3sARB(GLenum target, GLshort s, GLshort t, GLshort r) {
    glad_glMultiTexCoord3sARB = (PFNGLMULTITEXCOORD3SARBPROC) glad_gl_on_demand_loader("glMultiTexCoord3sARB");
    glad_glMultiTexCoord3sARB(target, s, t, r);
}
PFNGLMULTITEXCOORD3SARBPROC glad_glMultiTexCoord3sARB = glad_on_demand_impl_glMultiTexCoord3sARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord3svARB(GLenum target, const GLshort * v) {
    glad_glMultiTexCoord3svARB = (PFNGLMULTITEXCOORD3SVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord3svARB");
    glad_glMultiTexCoord3svARB(target, v);
}
PFNGLMULTITEXCOORD3SVARBPROC glad_glMultiTexCoord3svARB = glad_on_demand_impl_glMultiTexCoord3svARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
    glad_glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DARBPROC) glad_gl_on_demand_loader("glMultiTexCoord4dARB");
    glad_glMultiTexCoord4dARB(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4DARBPROC glad_glMultiTexCoord4dARB = glad_on_demand_impl_glMultiTexCoord4dARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4dvARB(GLenum target, const GLdouble * v) {
    glad_glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord4dvARB");
    glad_glMultiTexCoord4dvARB(target, v);
}
PFNGLMULTITEXCOORD4DVARBPROC glad_glMultiTexCoord4dvARB = glad_on_demand_impl_glMultiTexCoord4dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
    glad_glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC) glad_gl_on_demand_loader("glMultiTexCoord4fARB");
    glad_glMultiTexCoord4fARB(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4FARBPROC glad_glMultiTexCoord4fARB = glad_on_demand_impl_glMultiTexCoord4fARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4fvARB(GLenum target, const GLfloat * v) {
    glad_glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord4fvARB");
    glad_glMultiTexCoord4fvARB(target, v);
}
PFNGLMULTITEXCOORD4FVARBPROC glad_glMultiTexCoord4fvARB = glad_on_demand_impl_glMultiTexCoord4fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4iARB(GLenum target, GLint s, GLint t, GLint r, GLint q) {
    glad_glMultiTexCoord4iARB = (PFNGLMULTITEXCOORD4IARBPROC) glad_gl_on_demand_loader("glMultiTexCoord4iARB");
    glad_glMultiTexCoord4iARB(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4IARBPROC glad_glMultiTexCoord4iARB = glad_on_demand_impl_glMultiTexCoord4iARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4ivARB(GLenum target, const GLint * v) {
    glad_glMultiTexCoord4ivARB = (PFNGLMULTITEXCOORD4IVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord4ivARB");
    glad_glMultiTexCoord4ivARB(target, v);
}
PFNGLMULTITEXCOORD4IVARBPROC glad_glMultiTexCoord4ivARB = glad_on_demand_impl_glMultiTexCoord4ivARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4sARB(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) {
    glad_glMultiTexCoord4sARB = (PFNGLMULTITEXCOORD4SARBPROC) glad_gl_on_demand_loader("glMultiTexCoord4sARB");
    glad_glMultiTexCoord4sARB(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4SARBPROC glad_glMultiTexCoord4sARB = glad_on_demand_impl_glMultiTexCoord4sARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoord4svARB(GLenum target, const GLshort * v) {
    glad_glMultiTexCoord4svARB = (PFNGLMULTITEXCOORD4SVARBPROC) glad_gl_on_demand_loader("glMultiTexCoord4svARB");
    glad_glMultiTexCoord4svARB(target, v);
}
PFNGLMULTITEXCOORD4SVARBPROC glad_glMultiTexCoord4svARB = glad_on_demand_impl_glMultiTexCoord4svARB;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexCoordPointerEXT(GLenum texunit, GLint size, GLenum type, GLsizei stride, const void * pointer) {
    glad_glMultiTexCoordPointerEXT = (PFNGLMULTITEXCOORDPOINTEREXTPROC) glad_gl_on_demand_loader("glMultiTexCoordPointerEXT");
    glad_glMultiTexCoordPointerEXT(texunit, size, type, stride, pointer);
}
PFNGLMULTITEXCOORDPOINTEREXTPROC glad_glMultiTexCoordPointerEXT = glad_on_demand_impl_glMultiTexCoordPointerEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexEnvfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param) {
    glad_glMultiTexEnvfEXT = (PFNGLMULTITEXENVFEXTPROC) glad_gl_on_demand_loader("glMultiTexEnvfEXT");
    glad_glMultiTexEnvfEXT(texunit, target, pname, param);
}
PFNGLMULTITEXENVFEXTPROC glad_glMultiTexEnvfEXT = glad_on_demand_impl_glMultiTexEnvfEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat * params) {
    glad_glMultiTexEnvfvEXT = (PFNGLMULTITEXENVFVEXTPROC) glad_gl_on_demand_loader("glMultiTexEnvfvEXT");
    glad_glMultiTexEnvfvEXT(texunit, target, pname, params);
}
PFNGLMULTITEXENVFVEXTPROC glad_glMultiTexEnvfvEXT = glad_on_demand_impl_glMultiTexEnvfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexEnviEXT(GLenum texunit, GLenum target, GLenum pname, GLint param) {
    glad_glMultiTexEnviEXT = (PFNGLMULTITEXENVIEXTPROC) glad_gl_on_demand_loader("glMultiTexEnviEXT");
    glad_glMultiTexEnviEXT(texunit, target, pname, param);
}
PFNGLMULTITEXENVIEXTPROC glad_glMultiTexEnviEXT = glad_on_demand_impl_glMultiTexEnviEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint * params) {
    glad_glMultiTexEnvivEXT = (PFNGLMULTITEXENVIVEXTPROC) glad_gl_on_demand_loader("glMultiTexEnvivEXT");
    glad_glMultiTexEnvivEXT(texunit, target, pname, params);
}
PFNGLMULTITEXENVIVEXTPROC glad_glMultiTexEnvivEXT = glad_on_demand_impl_glMultiTexEnvivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexGendEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble param) {
    glad_glMultiTexGendEXT = (PFNGLMULTITEXGENDEXTPROC) glad_gl_on_demand_loader("glMultiTexGendEXT");
    glad_glMultiTexGendEXT(texunit, coord, pname, param);
}
PFNGLMULTITEXGENDEXTPROC glad_glMultiTexGendEXT = glad_on_demand_impl_glMultiTexGendEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLdouble * params) {
    glad_glMultiTexGendvEXT = (PFNGLMULTITEXGENDVEXTPROC) glad_gl_on_demand_loader("glMultiTexGendvEXT");
    glad_glMultiTexGendvEXT(texunit, coord, pname, params);
}
PFNGLMULTITEXGENDVEXTPROC glad_glMultiTexGendvEXT = glad_on_demand_impl_glMultiTexGendvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexGenfEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat param) {
    glad_glMultiTexGenfEXT = (PFNGLMULTITEXGENFEXTPROC) glad_gl_on_demand_loader("glMultiTexGenfEXT");
    glad_glMultiTexGenfEXT(texunit, coord, pname, param);
}
PFNGLMULTITEXGENFEXTPROC glad_glMultiTexGenfEXT = glad_on_demand_impl_glMultiTexGenfEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLfloat * params) {
    glad_glMultiTexGenfvEXT = (PFNGLMULTITEXGENFVEXTPROC) glad_gl_on_demand_loader("glMultiTexGenfvEXT");
    glad_glMultiTexGenfvEXT(texunit, coord, pname, params);
}
PFNGLMULTITEXGENFVEXTPROC glad_glMultiTexGenfvEXT = glad_on_demand_impl_glMultiTexGenfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexGeniEXT(GLenum texunit, GLenum coord, GLenum pname, GLint param) {
    glad_glMultiTexGeniEXT = (PFNGLMULTITEXGENIEXTPROC) glad_gl_on_demand_loader("glMultiTexGeniEXT");
    glad_glMultiTexGeniEXT(texunit, coord, pname, param);
}
PFNGLMULTITEXGENIEXTPROC glad_glMultiTexGeniEXT = glad_on_demand_impl_glMultiTexGeniEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, const GLint * params) {
    glad_glMultiTexGenivEXT = (PFNGLMULTITEXGENIVEXTPROC) glad_gl_on_demand_loader("glMultiTexGenivEXT");
    glad_glMultiTexGenivEXT(texunit, coord, pname, params);
}
PFNGLMULTITEXGENIVEXTPROC glad_glMultiTexGenivEXT = glad_on_demand_impl_glMultiTexGenivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glMultiTexImage1DEXT = (PFNGLMULTITEXIMAGE1DEXTPROC) glad_gl_on_demand_loader("glMultiTexImage1DEXT");
    glad_glMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, format, type, pixels);
}
PFNGLMULTITEXIMAGE1DEXTPROC glad_glMultiTexImage1DEXT = glad_on_demand_impl_glMultiTexImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glMultiTexImage2DEXT = (PFNGLMULTITEXIMAGE2DEXTPROC) glad_gl_on_demand_loader("glMultiTexImage2DEXT");
    glad_glMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, format, type, pixels);
}
PFNGLMULTITEXIMAGE2DEXTPROC glad_glMultiTexImage2DEXT = glad_on_demand_impl_glMultiTexImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glMultiTexImage3DEXT = (PFNGLMULTITEXIMAGE3DEXTPROC) glad_gl_on_demand_loader("glMultiTexImage3DEXT");
    glad_glMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, format, type, pixels);
}
PFNGLMULTITEXIMAGE3DEXTPROC glad_glMultiTexImage3DEXT = glad_on_demand_impl_glMultiTexImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint * params) {
    glad_glMultiTexParameterIivEXT = (PFNGLMULTITEXPARAMETERIIVEXTPROC) glad_gl_on_demand_loader("glMultiTexParameterIivEXT");
    glad_glMultiTexParameterIivEXT(texunit, target, pname, params);
}
PFNGLMULTITEXPARAMETERIIVEXTPROC glad_glMultiTexParameterIivEXT = glad_on_demand_impl_glMultiTexParameterIivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, const GLuint * params) {
    glad_glMultiTexParameterIuivEXT = (PFNGLMULTITEXPARAMETERIUIVEXTPROC) glad_gl_on_demand_loader("glMultiTexParameterIuivEXT");
    glad_glMultiTexParameterIuivEXT(texunit, target, pname, params);
}
PFNGLMULTITEXPARAMETERIUIVEXTPROC glad_glMultiTexParameterIuivEXT = glad_on_demand_impl_glMultiTexParameterIuivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexParameterfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param) {
    glad_glMultiTexParameterfEXT = (PFNGLMULTITEXPARAMETERFEXTPROC) glad_gl_on_demand_loader("glMultiTexParameterfEXT");
    glad_glMultiTexParameterfEXT(texunit, target, pname, param);
}
PFNGLMULTITEXPARAMETERFEXTPROC glad_glMultiTexParameterfEXT = glad_on_demand_impl_glMultiTexParameterfEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat * params) {
    glad_glMultiTexParameterfvEXT = (PFNGLMULTITEXPARAMETERFVEXTPROC) glad_gl_on_demand_loader("glMultiTexParameterfvEXT");
    glad_glMultiTexParameterfvEXT(texunit, target, pname, params);
}
PFNGLMULTITEXPARAMETERFVEXTPROC glad_glMultiTexParameterfvEXT = glad_on_demand_impl_glMultiTexParameterfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexParameteriEXT(GLenum texunit, GLenum target, GLenum pname, GLint param) {
    glad_glMultiTexParameteriEXT = (PFNGLMULTITEXPARAMETERIEXTPROC) glad_gl_on_demand_loader("glMultiTexParameteriEXT");
    glad_glMultiTexParameteriEXT(texunit, target, pname, param);
}
PFNGLMULTITEXPARAMETERIEXTPROC glad_glMultiTexParameteriEXT = glad_on_demand_impl_glMultiTexParameteriEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint * params) {
    glad_glMultiTexParameterivEXT = (PFNGLMULTITEXPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glMultiTexParameterivEXT");
    glad_glMultiTexParameterivEXT(texunit, target, pname, params);
}
PFNGLMULTITEXPARAMETERIVEXTPROC glad_glMultiTexParameterivEXT = glad_on_demand_impl_glMultiTexParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexRenderbufferEXT(GLenum texunit, GLenum target, GLuint renderbuffer) {
    glad_glMultiTexRenderbufferEXT = (PFNGLMULTITEXRENDERBUFFEREXTPROC) glad_gl_on_demand_loader("glMultiTexRenderbufferEXT");
    glad_glMultiTexRenderbufferEXT(texunit, target, renderbuffer);
}
PFNGLMULTITEXRENDERBUFFEREXTPROC glad_glMultiTexRenderbufferEXT = glad_on_demand_impl_glMultiTexRenderbufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels) {
    glad_glMultiTexSubImage1DEXT = (PFNGLMULTITEXSUBIMAGE1DEXTPROC) glad_gl_on_demand_loader("glMultiTexSubImage1DEXT");
    glad_glMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, type, pixels);
}
PFNGLMULTITEXSUBIMAGE1DEXTPROC glad_glMultiTexSubImage1DEXT = glad_on_demand_impl_glMultiTexSubImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) {
    glad_glMultiTexSubImage2DEXT = (PFNGLMULTITEXSUBIMAGE2DEXTPROC) glad_gl_on_demand_loader("glMultiTexSubImage2DEXT");
    glad_glMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, type, pixels);
}
PFNGLMULTITEXSUBIMAGE2DEXTPROC glad_glMultiTexSubImage2DEXT = glad_on_demand_impl_glMultiTexSubImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels) {
    glad_glMultiTexSubImage3DEXT = (PFNGLMULTITEXSUBIMAGE3DEXTPROC) glad_gl_on_demand_loader("glMultiTexSubImage3DEXT");
    glad_glMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}
PFNGLMULTITEXSUBIMAGE3DEXTPROC glad_glMultiTexSubImage3DEXT = glad_on_demand_impl_glMultiTexSubImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedBufferDataEXT(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage) {
    glad_glNamedBufferDataEXT = (PFNGLNAMEDBUFFERDATAEXTPROC) glad_gl_on_demand_loader("glNamedBufferDataEXT");
    glad_glNamedBufferDataEXT(buffer, size, data, usage);
}
PFNGLNAMEDBUFFERDATAEXTPROC glad_glNamedBufferDataEXT = glad_on_demand_impl_glNamedBufferDataEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedBufferStorageEXT(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags) {
    glad_glNamedBufferStorageEXT = (PFNGLNAMEDBUFFERSTORAGEEXTPROC) glad_gl_on_demand_loader("glNamedBufferStorageEXT");
    glad_glNamedBufferStorageEXT(buffer, size, data, flags);
}
PFNGLNAMEDBUFFERSTORAGEEXTPROC glad_glNamedBufferStorageEXT = glad_on_demand_impl_glNamedBufferStorageEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data) {
    glad_glNamedBufferSubDataEXT = (PFNGLNAMEDBUFFERSUBDATAEXTPROC) glad_gl_on_demand_loader("glNamedBufferSubDataEXT");
    glad_glNamedBufferSubDataEXT(buffer, offset, size, data);
}
PFNGLNAMEDBUFFERSUBDATAEXTPROC glad_glNamedBufferSubDataEXT = glad_on_demand_impl_glNamedBufferSubDataEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedCopyBufferSubDataEXT(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
    glad_glNamedCopyBufferSubDataEXT = (PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC) glad_gl_on_demand_loader("glNamedCopyBufferSubDataEXT");
    glad_glNamedCopyBufferSubDataEXT(readBuffer, writeBuffer, readOffset, writeOffset, size);
}
PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC glad_glNamedCopyBufferSubDataEXT = glad_on_demand_impl_glNamedCopyBufferSubDataEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedFramebufferParameteriEXT(GLuint framebuffer, GLenum pname, GLint param) {
    glad_glNamedFramebufferParameteriEXT = (PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC) glad_gl_on_demand_loader("glNamedFramebufferParameteriEXT");
    glad_glNamedFramebufferParameteriEXT(framebuffer, pname, param);
}
PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC glad_glNamedFramebufferParameteriEXT = glad_on_demand_impl_glNamedFramebufferParameteriEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedFramebufferRenderbufferEXT(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    glad_glNamedFramebufferRenderbufferEXT = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC) glad_gl_on_demand_loader("glNamedFramebufferRenderbufferEXT");
    glad_glNamedFramebufferRenderbufferEXT(framebuffer, attachment, renderbuffertarget, renderbuffer);
}
PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC glad_glNamedFramebufferRenderbufferEXT = glad_on_demand_impl_glNamedFramebufferRenderbufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedFramebufferTexture1DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glad_glNamedFramebufferTexture1DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC) glad_gl_on_demand_loader("glNamedFramebufferTexture1DEXT");
    glad_glNamedFramebufferTexture1DEXT(framebuffer, attachment, textarget, texture, level);
}
PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC glad_glNamedFramebufferTexture1DEXT = glad_on_demand_impl_glNamedFramebufferTexture1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedFramebufferTexture2DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glad_glNamedFramebufferTexture2DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC) glad_gl_on_demand_loader("glNamedFramebufferTexture2DEXT");
    glad_glNamedFramebufferTexture2DEXT(framebuffer, attachment, textarget, texture, level);
}
PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC glad_glNamedFramebufferTexture2DEXT = glad_on_demand_impl_glNamedFramebufferTexture2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedFramebufferTexture3DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) {
    glad_glNamedFramebufferTexture3DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC) glad_gl_on_demand_loader("glNamedFramebufferTexture3DEXT");
    glad_glNamedFramebufferTexture3DEXT(framebuffer, attachment, textarget, texture, level, zoffset);
}
PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC glad_glNamedFramebufferTexture3DEXT = glad_on_demand_impl_glNamedFramebufferTexture3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedFramebufferTextureEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) {
    glad_glNamedFramebufferTextureEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC) glad_gl_on_demand_loader("glNamedFramebufferTextureEXT");
    glad_glNamedFramebufferTextureEXT(framebuffer, attachment, texture, level);
}
PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC glad_glNamedFramebufferTextureEXT = glad_on_demand_impl_glNamedFramebufferTextureEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedFramebufferTextureFaceEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face) {
    glad_glNamedFramebufferTextureFaceEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC) glad_gl_on_demand_loader("glNamedFramebufferTextureFaceEXT");
    glad_glNamedFramebufferTextureFaceEXT(framebuffer, attachment, texture, level, face);
}
PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC glad_glNamedFramebufferTextureFaceEXT = glad_on_demand_impl_glNamedFramebufferTextureFaceEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedFramebufferTextureLayerEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) {
    glad_glNamedFramebufferTextureLayerEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC) glad_gl_on_demand_loader("glNamedFramebufferTextureLayerEXT");
    glad_glNamedFramebufferTextureLayerEXT(framebuffer, attachment, texture, level, layer);
}
PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC glad_glNamedFramebufferTextureLayerEXT = glad_on_demand_impl_glNamedFramebufferTextureLayerEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParameter4dEXT(GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glNamedProgramLocalParameter4dEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParameter4dEXT");
    glad_glNamedProgramLocalParameter4dEXT(program, target, index, x, y, z, w);
}
PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC glad_glNamedProgramLocalParameter4dEXT = glad_on_demand_impl_glNamedProgramLocalParameter4dEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParameter4dvEXT(GLuint program, GLenum target, GLuint index, const GLdouble * params) {
    glad_glNamedProgramLocalParameter4dvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParameter4dvEXT");
    glad_glNamedProgramLocalParameter4dvEXT(program, target, index, params);
}
PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC glad_glNamedProgramLocalParameter4dvEXT = glad_on_demand_impl_glNamedProgramLocalParameter4dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParameter4fEXT(GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glNamedProgramLocalParameter4fEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParameter4fEXT");
    glad_glNamedProgramLocalParameter4fEXT(program, target, index, x, y, z, w);
}
PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC glad_glNamedProgramLocalParameter4fEXT = glad_on_demand_impl_glNamedProgramLocalParameter4fEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParameter4fvEXT(GLuint program, GLenum target, GLuint index, const GLfloat * params) {
    glad_glNamedProgramLocalParameter4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParameter4fvEXT");
    glad_glNamedProgramLocalParameter4fvEXT(program, target, index, params);
}
PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC glad_glNamedProgramLocalParameter4fvEXT = glad_on_demand_impl_glNamedProgramLocalParameter4fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParameterI4iEXT(GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) {
    glad_glNamedProgramLocalParameterI4iEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParameterI4iEXT");
    glad_glNamedProgramLocalParameterI4iEXT(program, target, index, x, y, z, w);
}
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC glad_glNamedProgramLocalParameterI4iEXT = glad_on_demand_impl_glNamedProgramLocalParameterI4iEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParameterI4ivEXT(GLuint program, GLenum target, GLuint index, const GLint * params) {
    glad_glNamedProgramLocalParameterI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParameterI4ivEXT");
    glad_glNamedProgramLocalParameterI4ivEXT(program, target, index, params);
}
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC glad_glNamedProgramLocalParameterI4ivEXT = glad_on_demand_impl_glNamedProgramLocalParameterI4ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParameterI4uiEXT(GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
    glad_glNamedProgramLocalParameterI4uiEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParameterI4uiEXT");
    glad_glNamedProgramLocalParameterI4uiEXT(program, target, index, x, y, z, w);
}
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC glad_glNamedProgramLocalParameterI4uiEXT = glad_on_demand_impl_glNamedProgramLocalParameterI4uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParameterI4uivEXT(GLuint program, GLenum target, GLuint index, const GLuint * params) {
    glad_glNamedProgramLocalParameterI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParameterI4uivEXT");
    glad_glNamedProgramLocalParameterI4uivEXT(program, target, index, params);
}
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC glad_glNamedProgramLocalParameterI4uivEXT = glad_on_demand_impl_glNamedProgramLocalParameterI4uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParameters4fvEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat * params) {
    glad_glNamedProgramLocalParameters4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParameters4fvEXT");
    glad_glNamedProgramLocalParameters4fvEXT(program, target, index, count, params);
}
PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC glad_glNamedProgramLocalParameters4fvEXT = glad_on_demand_impl_glNamedProgramLocalParameters4fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParametersI4ivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLint * params) {
    glad_glNamedProgramLocalParametersI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParametersI4ivEXT");
    glad_glNamedProgramLocalParametersI4ivEXT(program, target, index, count, params);
}
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC glad_glNamedProgramLocalParametersI4ivEXT = glad_on_demand_impl_glNamedProgramLocalParametersI4ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramLocalParametersI4uivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint * params) {
    glad_glNamedProgramLocalParametersI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC) glad_gl_on_demand_loader("glNamedProgramLocalParametersI4uivEXT");
    glad_glNamedProgramLocalParametersI4uivEXT(program, target, index, count, params);
}
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC glad_glNamedProgramLocalParametersI4uivEXT = glad_on_demand_impl_glNamedProgramLocalParametersI4uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedProgramStringEXT(GLuint program, GLenum target, GLenum format, GLsizei len, const void * string) {
    glad_glNamedProgramStringEXT = (PFNGLNAMEDPROGRAMSTRINGEXTPROC) glad_gl_on_demand_loader("glNamedProgramStringEXT");
    glad_glNamedProgramStringEXT(program, target, format, len, string);
}
PFNGLNAMEDPROGRAMSTRINGEXTPROC glad_glNamedProgramStringEXT = glad_on_demand_impl_glNamedProgramStringEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedRenderbufferStorageEXT(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glNamedRenderbufferStorageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC) glad_gl_on_demand_loader("glNamedRenderbufferStorageEXT");
    glad_glNamedRenderbufferStorageEXT(renderbuffer, internalformat, width, height);
}
PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC glad_glNamedRenderbufferStorageEXT = glad_on_demand_impl_glNamedRenderbufferStorageEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedRenderbufferStorageMultisampleCoverageEXT(GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glNamedRenderbufferStorageMultisampleCoverageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC) glad_gl_on_demand_loader("glNamedRenderbufferStorageMultisampleCoverageEXT");
    glad_glNamedRenderbufferStorageMultisampleCoverageEXT(renderbuffer, coverageSamples, colorSamples, internalformat, width, height);
}
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC glad_glNamedRenderbufferStorageMultisampleCoverageEXT = glad_on_demand_impl_glNamedRenderbufferStorageMultisampleCoverageEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNamedRenderbufferStorageMultisampleEXT(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glNamedRenderbufferStorageMultisampleEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) glad_gl_on_demand_loader("glNamedRenderbufferStorageMultisampleEXT");
    glad_glNamedRenderbufferStorageMultisampleEXT(renderbuffer, samples, internalformat, width, height);
}
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glad_glNamedRenderbufferStorageMultisampleEXT = glad_on_demand_impl_glNamedRenderbufferStorageMultisampleEXT;
static void GLAD_API_PTR glad_on_demand_impl_glNormalPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void * pointer) {
    glad_glNormalPointerEXT = (PFNGLNORMALPOINTEREXTPROC) glad_gl_on_demand_loader("glNormalPointerEXT");
    glad_glNormalPointerEXT(type, stride, count, pointer);
}
PFNGLNORMALPOINTEREXTPROC glad_glNormalPointerEXT = glad_on_demand_impl_glNormalPointerEXT;
static void GLAD_API_PTR glad_on_demand_impl_glPixelStoref(GLenum pname, GLfloat param) {
    glad_glPixelStoref = (PFNGLPIXELSTOREFPROC) glad_gl_on_demand_loader("glPixelStoref");
    glad_glPixelStoref(pname, param);
}
PFNGLPIXELSTOREFPROC glad_glPixelStoref = glad_on_demand_impl_glPixelStoref;
static void GLAD_API_PTR glad_on_demand_impl_glPixelStorei(GLenum pname, GLint param) {
    glad_glPixelStorei = (PFNGLPIXELSTOREIPROC) glad_gl_on_demand_loader("glPixelStorei");
    glad_glPixelStorei(pname, param);
}
PFNGLPIXELSTOREIPROC glad_glPixelStorei = glad_on_demand_impl_glPixelStorei;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterf(GLenum pname, GLfloat param) {
    glad_glPointParameterf = (PFNGLPOINTPARAMETERFPROC) glad_gl_on_demand_loader("glPointParameterf");
    glad_glPointParameterf(pname, param);
}
PFNGLPOINTPARAMETERFPROC glad_glPointParameterf = glad_on_demand_impl_glPointParameterf;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterfARB(GLenum pname, GLfloat param) {
    glad_glPointParameterfARB = (PFNGLPOINTPARAMETERFARBPROC) glad_gl_on_demand_loader("glPointParameterfARB");
    glad_glPointParameterfARB(pname, param);
}
PFNGLPOINTPARAMETERFARBPROC glad_glPointParameterfARB = glad_on_demand_impl_glPointParameterfARB;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterfEXT(GLenum pname, GLfloat param) {
    glad_glPointParameterfEXT = (PFNGLPOINTPARAMETERFEXTPROC) glad_gl_on_demand_loader("glPointParameterfEXT");
    glad_glPointParameterfEXT(pname, param);
}
PFNGLPOINTPARAMETERFEXTPROC glad_glPointParameterfEXT = glad_on_demand_impl_glPointParameterfEXT;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterfSGIS(GLenum pname, GLfloat param) {
    glad_glPointParameterfSGIS = (PFNGLPOINTPARAMETERFSGISPROC) glad_gl_on_demand_loader("glPointParameterfSGIS");
    glad_glPointParameterfSGIS(pname, param);
}
PFNGLPOINTPARAMETERFSGISPROC glad_glPointParameterfSGIS = glad_on_demand_impl_glPointParameterfSGIS;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterfv(GLenum pname, const GLfloat * params) {
    glad_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC) glad_gl_on_demand_loader("glPointParameterfv");
    glad_glPointParameterfv(pname, params);
}
PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv = glad_on_demand_impl_glPointParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterfvARB(GLenum pname, const GLfloat * params) {
    glad_glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC) glad_gl_on_demand_loader("glPointParameterfvARB");
    glad_glPointParameterfvARB(pname, params);
}
PFNGLPOINTPARAMETERFVARBPROC glad_glPointParameterfvARB = glad_on_demand_impl_glPointParameterfvARB;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterfvEXT(GLenum pname, const GLfloat * params) {
    glad_glPointParameterfvEXT = (PFNGLPOINTPARAMETERFVEXTPROC) glad_gl_on_demand_loader("glPointParameterfvEXT");
    glad_glPointParameterfvEXT(pname, params);
}
PFNGLPOINTPARAMETERFVEXTPROC glad_glPointParameterfvEXT = glad_on_demand_impl_glPointParameterfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterfvSGIS(GLenum pname, const GLfloat * params) {
    glad_glPointParameterfvSGIS = (PFNGLPOINTPARAMETERFVSGISPROC) glad_gl_on_demand_loader("glPointParameterfvSGIS");
    glad_glPointParameterfvSGIS(pname, params);
}
PFNGLPOINTPARAMETERFVSGISPROC glad_glPointParameterfvSGIS = glad_on_demand_impl_glPointParameterfvSGIS;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameteri(GLenum pname, GLint param) {
    glad_glPointParameteri = (PFNGLPOINTPARAMETERIPROC) glad_gl_on_demand_loader("glPointParameteri");
    glad_glPointParameteri(pname, param);
}
PFNGLPOINTPARAMETERIPROC glad_glPointParameteri = glad_on_demand_impl_glPointParameteri;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameteriNV(GLenum pname, GLint param) {
    glad_glPointParameteriNV = (PFNGLPOINTPARAMETERINVPROC) glad_gl_on_demand_loader("glPointParameteriNV");
    glad_glPointParameteriNV(pname, param);
}
PFNGLPOINTPARAMETERINVPROC glad_glPointParameteriNV = glad_on_demand_impl_glPointParameteriNV;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameteriv(GLenum pname, const GLint * params) {
    glad_glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC) glad_gl_on_demand_loader("glPointParameteriv");
    glad_glPointParameteriv(pname, params);
}
PFNGLPOINTPARAMETERIVPROC glad_glPointParameteriv = glad_on_demand_impl_glPointParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glPointParameterivNV(GLenum pname, const GLint * params) {
    glad_glPointParameterivNV = (PFNGLPOINTPARAMETERIVNVPROC) glad_gl_on_demand_loader("glPointParameterivNV");
    glad_glPointParameterivNV(pname, params);
}
PFNGLPOINTPARAMETERIVNVPROC glad_glPointParameterivNV = glad_on_demand_impl_glPointParameterivNV;
static void GLAD_API_PTR glad_on_demand_impl_glPointSize(GLfloat size) {
    glad_glPointSize = (PFNGLPOINTSIZEPROC) glad_gl_on_demand_loader("glPointSize");
    glad_glPointSize(size);
}
PFNGLPOINTSIZEPROC glad_glPointSize = glad_on_demand_impl_glPointSize;
static void GLAD_API_PTR glad_on_demand_impl_glPolygonMode(GLenum face, GLenum mode) {
    glad_glPolygonMode = (PFNGLPOLYGONMODEPROC) glad_gl_on_demand_loader("glPolygonMode");
    glad_glPolygonMode(face, mode);
}
PFNGLPOLYGONMODEPROC glad_glPolygonMode = glad_on_demand_impl_glPolygonMode;
static void GLAD_API_PTR glad_on_demand_impl_glPolygonOffset(GLfloat factor, GLfloat units) {
    glad_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC) glad_gl_on_demand_loader("glPolygonOffset");
    glad_glPolygonOffset(factor, units);
}
PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset = glad_on_demand_impl_glPolygonOffset;
static void GLAD_API_PTR glad_on_demand_impl_glPrimitiveRestartIndex(GLuint index) {
    glad_glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC) glad_gl_on_demand_loader("glPrimitiveRestartIndex");
    glad_glPrimitiveRestartIndex(index);
}
PFNGLPRIMITIVERESTARTINDEXPROC glad_glPrimitiveRestartIndex = glad_on_demand_impl_glPrimitiveRestartIndex;
static void GLAD_API_PTR glad_on_demand_impl_glPrioritizeTexturesEXT(GLsizei n, const GLuint * textures, const GLclampf * priorities) {
    glad_glPrioritizeTexturesEXT = (PFNGLPRIORITIZETEXTURESEXTPROC) glad_gl_on_demand_loader("glPrioritizeTexturesEXT");
    glad_glPrioritizeTexturesEXT(n, textures, priorities);
}
PFNGLPRIORITIZETEXTURESEXTPROC glad_glPrioritizeTexturesEXT = glad_on_demand_impl_glPrioritizeTexturesEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramEnvParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glProgramEnvParameter4dARB = (PFNGLPROGRAMENVPARAMETER4DARBPROC) glad_gl_on_demand_loader("glProgramEnvParameter4dARB");
    glad_glProgramEnvParameter4dARB(target, index, x, y, z, w);
}
PFNGLPROGRAMENVPARAMETER4DARBPROC glad_glProgramEnvParameter4dARB = glad_on_demand_impl_glProgramEnvParameter4dARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramEnvParameter4dvARB(GLenum target, GLuint index, const GLdouble * params) {
    glad_glProgramEnvParameter4dvARB = (PFNGLPROGRAMENVPARAMETER4DVARBPROC) glad_gl_on_demand_loader("glProgramEnvParameter4dvARB");
    glad_glProgramEnvParameter4dvARB(target, index, params);
}
PFNGLPROGRAMENVPARAMETER4DVARBPROC glad_glProgramEnvParameter4dvARB = glad_on_demand_impl_glProgramEnvParameter4dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramEnvParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glProgramEnvParameter4fARB = (PFNGLPROGRAMENVPARAMETER4FARBPROC) glad_gl_on_demand_loader("glProgramEnvParameter4fARB");
    glad_glProgramEnvParameter4fARB(target, index, x, y, z, w);
}
PFNGLPROGRAMENVPARAMETER4FARBPROC glad_glProgramEnvParameter4fARB = glad_on_demand_impl_glProgramEnvParameter4fARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramEnvParameter4fvARB(GLenum target, GLuint index, const GLfloat * params) {
    glad_glProgramEnvParameter4fvARB = (PFNGLPROGRAMENVPARAMETER4FVARBPROC) glad_gl_on_demand_loader("glProgramEnvParameter4fvARB");
    glad_glProgramEnvParameter4fvARB(target, index, params);
}
PFNGLPROGRAMENVPARAMETER4FVARBPROC glad_glProgramEnvParameter4fvARB = glad_on_demand_impl_glProgramEnvParameter4fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramLocalParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glProgramLocalParameter4dARB = (PFNGLPROGRAMLOCALPARAMETER4DARBPROC) glad_gl_on_demand_loader("glProgramLocalParameter4dARB");
    glad_glProgramLocalParameter4dARB(target, index, x, y, z, w);
}
PFNGLPROGRAMLOCALPARAMETER4DARBPROC glad_glProgramLocalParameter4dARB = glad_on_demand_impl_glProgramLocalParameter4dARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramLocalParameter4dvARB(GLenum target, GLuint index, const GLdouble * params) {
    glad_glProgramLocalParameter4dvARB = (PFNGLPROGRAMLOCALPARAMETER4DVARBPROC) glad_gl_on_demand_loader("glProgramLocalParameter4dvARB");
    glad_glProgramLocalParameter4dvARB(target, index, params);
}
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC glad_glProgramLocalParameter4dvARB = glad_on_demand_impl_glProgramLocalParameter4dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramLocalParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glProgramLocalParameter4fARB = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC) glad_gl_on_demand_loader("glProgramLocalParameter4fARB");
    glad_glProgramLocalParameter4fARB(target, index, x, y, z, w);
}
PFNGLPROGRAMLOCALPARAMETER4FARBPROC glad_glProgramLocalParameter4fARB = glad_on_demand_impl_glProgramLocalParameter4fARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramLocalParameter4fvARB(GLenum target, GLuint index, const GLfloat * params) {
    glad_glProgramLocalParameter4fvARB = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC) glad_gl_on_demand_loader("glProgramLocalParameter4fvARB");
    glad_glProgramLocalParameter4fvARB(target, index, params);
}
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC glad_glProgramLocalParameter4fvARB = glad_on_demand_impl_glProgramLocalParameter4fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramParameter4dNV(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glProgramParameter4dNV = (PFNGLPROGRAMPARAMETER4DNVPROC) glad_gl_on_demand_loader("glProgramParameter4dNV");
    glad_glProgramParameter4dNV(target, index, x, y, z, w);
}
PFNGLPROGRAMPARAMETER4DNVPROC glad_glProgramParameter4dNV = glad_on_demand_impl_glProgramParameter4dNV;
static void GLAD_API_PTR glad_on_demand_impl_glProgramParameter4dvNV(GLenum target, GLuint index, const GLdouble * v) {
    glad_glProgramParameter4dvNV = (PFNGLPROGRAMPARAMETER4DVNVPROC) glad_gl_on_demand_loader("glProgramParameter4dvNV");
    glad_glProgramParameter4dvNV(target, index, v);
}
PFNGLPROGRAMPARAMETER4DVNVPROC glad_glProgramParameter4dvNV = glad_on_demand_impl_glProgramParameter4dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glProgramParameter4fNV(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glProgramParameter4fNV = (PFNGLPROGRAMPARAMETER4FNVPROC) glad_gl_on_demand_loader("glProgramParameter4fNV");
    glad_glProgramParameter4fNV(target, index, x, y, z, w);
}
PFNGLPROGRAMPARAMETER4FNVPROC glad_glProgramParameter4fNV = glad_on_demand_impl_glProgramParameter4fNV;
static void GLAD_API_PTR glad_on_demand_impl_glProgramParameter4fvNV(GLenum target, GLuint index, const GLfloat * v) {
    glad_glProgramParameter4fvNV = (PFNGLPROGRAMPARAMETER4FVNVPROC) glad_gl_on_demand_loader("glProgramParameter4fvNV");
    glad_glProgramParameter4fvNV(target, index, v);
}
PFNGLPROGRAMPARAMETER4FVNVPROC glad_glProgramParameter4fvNV = glad_on_demand_impl_glProgramParameter4fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glProgramParameteriARB(GLuint program, GLenum pname, GLint value) {
    glad_glProgramParameteriARB = (PFNGLPROGRAMPARAMETERIARBPROC) glad_gl_on_demand_loader("glProgramParameteriARB");
    glad_glProgramParameteriARB(program, pname, value);
}
PFNGLPROGRAMPARAMETERIARBPROC glad_glProgramParameteriARB = glad_on_demand_impl_glProgramParameteriARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramParameters4dvNV(GLenum target, GLuint index, GLsizei count, const GLdouble * v) {
    glad_glProgramParameters4dvNV = (PFNGLPROGRAMPARAMETERS4DVNVPROC) glad_gl_on_demand_loader("glProgramParameters4dvNV");
    glad_glProgramParameters4dvNV(target, index, count, v);
}
PFNGLPROGRAMPARAMETERS4DVNVPROC glad_glProgramParameters4dvNV = glad_on_demand_impl_glProgramParameters4dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glProgramParameters4fvNV(GLenum target, GLuint index, GLsizei count, const GLfloat * v) {
    glad_glProgramParameters4fvNV = (PFNGLPROGRAMPARAMETERS4FVNVPROC) glad_gl_on_demand_loader("glProgramParameters4fvNV");
    glad_glProgramParameters4fvNV(target, index, count, v);
}
PFNGLPROGRAMPARAMETERS4FVNVPROC glad_glProgramParameters4fvNV = glad_on_demand_impl_glProgramParameters4fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glProgramStringARB(GLenum target, GLenum format, GLsizei len, const void * string) {
    glad_glProgramStringARB = (PFNGLPROGRAMSTRINGARBPROC) glad_gl_on_demand_loader("glProgramStringARB");
    glad_glProgramStringARB(target, format, len, string);
}
PFNGLPROGRAMSTRINGARBPROC glad_glProgramStringARB = glad_on_demand_impl_glProgramStringARB;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform1dEXT(GLuint program, GLint location, GLdouble x) {
    glad_glProgramUniform1dEXT = (PFNGLPROGRAMUNIFORM1DEXTPROC) glad_gl_on_demand_loader("glProgramUniform1dEXT");
    glad_glProgramUniform1dEXT(program, location, x);
}
PFNGLPROGRAMUNIFORM1DEXTPROC glad_glProgramUniform1dEXT = glad_on_demand_impl_glProgramUniform1dEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform1dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble * value) {
    glad_glProgramUniform1dvEXT = (PFNGLPROGRAMUNIFORM1DVEXTPROC) glad_gl_on_demand_loader("glProgramUniform1dvEXT");
    glad_glProgramUniform1dvEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM1DVEXTPROC glad_glProgramUniform1dvEXT = glad_on_demand_impl_glProgramUniform1dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform1fEXT(GLuint program, GLint location, GLfloat v0) {
    glad_glProgramUniform1fEXT = (PFNGLPROGRAMUNIFORM1FEXTPROC) glad_gl_on_demand_loader("glProgramUniform1fEXT");
    glad_glProgramUniform1fEXT(program, location, v0);
}
PFNGLPROGRAMUNIFORM1FEXTPROC glad_glProgramUniform1fEXT = glad_on_demand_impl_glProgramUniform1fEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat * value) {
    glad_glProgramUniform1fvEXT = (PFNGLPROGRAMUNIFORM1FVEXTPROC) glad_gl_on_demand_loader("glProgramUniform1fvEXT");
    glad_glProgramUniform1fvEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM1FVEXTPROC glad_glProgramUniform1fvEXT = glad_on_demand_impl_glProgramUniform1fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform1iEXT(GLuint program, GLint location, GLint v0) {
    glad_glProgramUniform1iEXT = (PFNGLPROGRAMUNIFORM1IEXTPROC) glad_gl_on_demand_loader("glProgramUniform1iEXT");
    glad_glProgramUniform1iEXT(program, location, v0);
}
PFNGLPROGRAMUNIFORM1IEXTPROC glad_glProgramUniform1iEXT = glad_on_demand_impl_glProgramUniform1iEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint * value) {
    glad_glProgramUniform1ivEXT = (PFNGLPROGRAMUNIFORM1IVEXTPROC) glad_gl_on_demand_loader("glProgramUniform1ivEXT");
    glad_glProgramUniform1ivEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM1IVEXTPROC glad_glProgramUniform1ivEXT = glad_on_demand_impl_glProgramUniform1ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform1uiEXT(GLuint program, GLint location, GLuint v0) {
    glad_glProgramUniform1uiEXT = (PFNGLPROGRAMUNIFORM1UIEXTPROC) glad_gl_on_demand_loader("glProgramUniform1uiEXT");
    glad_glProgramUniform1uiEXT(program, location, v0);
}
PFNGLPROGRAMUNIFORM1UIEXTPROC glad_glProgramUniform1uiEXT = glad_on_demand_impl_glProgramUniform1uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform1uivEXT(GLuint program, GLint location, GLsizei count, const GLuint * value) {
    glad_glProgramUniform1uivEXT = (PFNGLPROGRAMUNIFORM1UIVEXTPROC) glad_gl_on_demand_loader("glProgramUniform1uivEXT");
    glad_glProgramUniform1uivEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM1UIVEXTPROC glad_glProgramUniform1uivEXT = glad_on_demand_impl_glProgramUniform1uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform2dEXT(GLuint program, GLint location, GLdouble x, GLdouble y) {
    glad_glProgramUniform2dEXT = (PFNGLPROGRAMUNIFORM2DEXTPROC) glad_gl_on_demand_loader("glProgramUniform2dEXT");
    glad_glProgramUniform2dEXT(program, location, x, y);
}
PFNGLPROGRAMUNIFORM2DEXTPROC glad_glProgramUniform2dEXT = glad_on_demand_impl_glProgramUniform2dEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform2dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble * value) {
    glad_glProgramUniform2dvEXT = (PFNGLPROGRAMUNIFORM2DVEXTPROC) glad_gl_on_demand_loader("glProgramUniform2dvEXT");
    glad_glProgramUniform2dvEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM2DVEXTPROC glad_glProgramUniform2dvEXT = glad_on_demand_impl_glProgramUniform2dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform2fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1) {
    glad_glProgramUniform2fEXT = (PFNGLPROGRAMUNIFORM2FEXTPROC) glad_gl_on_demand_loader("glProgramUniform2fEXT");
    glad_glProgramUniform2fEXT(program, location, v0, v1);
}
PFNGLPROGRAMUNIFORM2FEXTPROC glad_glProgramUniform2fEXT = glad_on_demand_impl_glProgramUniform2fEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat * value) {
    glad_glProgramUniform2fvEXT = (PFNGLPROGRAMUNIFORM2FVEXTPROC) glad_gl_on_demand_loader("glProgramUniform2fvEXT");
    glad_glProgramUniform2fvEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM2FVEXTPROC glad_glProgramUniform2fvEXT = glad_on_demand_impl_glProgramUniform2fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform2iEXT(GLuint program, GLint location, GLint v0, GLint v1) {
    glad_glProgramUniform2iEXT = (PFNGLPROGRAMUNIFORM2IEXTPROC) glad_gl_on_demand_loader("glProgramUniform2iEXT");
    glad_glProgramUniform2iEXT(program, location, v0, v1);
}
PFNGLPROGRAMUNIFORM2IEXTPROC glad_glProgramUniform2iEXT = glad_on_demand_impl_glProgramUniform2iEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint * value) {
    glad_glProgramUniform2ivEXT = (PFNGLPROGRAMUNIFORM2IVEXTPROC) glad_gl_on_demand_loader("glProgramUniform2ivEXT");
    glad_glProgramUniform2ivEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM2IVEXTPROC glad_glProgramUniform2ivEXT = glad_on_demand_impl_glProgramUniform2ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform2uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1) {
    glad_glProgramUniform2uiEXT = (PFNGLPROGRAMUNIFORM2UIEXTPROC) glad_gl_on_demand_loader("glProgramUniform2uiEXT");
    glad_glProgramUniform2uiEXT(program, location, v0, v1);
}
PFNGLPROGRAMUNIFORM2UIEXTPROC glad_glProgramUniform2uiEXT = glad_on_demand_impl_glProgramUniform2uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform2uivEXT(GLuint program, GLint location, GLsizei count, const GLuint * value) {
    glad_glProgramUniform2uivEXT = (PFNGLPROGRAMUNIFORM2UIVEXTPROC) glad_gl_on_demand_loader("glProgramUniform2uivEXT");
    glad_glProgramUniform2uivEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM2UIVEXTPROC glad_glProgramUniform2uivEXT = glad_on_demand_impl_glProgramUniform2uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform3dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z) {
    glad_glProgramUniform3dEXT = (PFNGLPROGRAMUNIFORM3DEXTPROC) glad_gl_on_demand_loader("glProgramUniform3dEXT");
    glad_glProgramUniform3dEXT(program, location, x, y, z);
}
PFNGLPROGRAMUNIFORM3DEXTPROC glad_glProgramUniform3dEXT = glad_on_demand_impl_glProgramUniform3dEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform3dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble * value) {
    glad_glProgramUniform3dvEXT = (PFNGLPROGRAMUNIFORM3DVEXTPROC) glad_gl_on_demand_loader("glProgramUniform3dvEXT");
    glad_glProgramUniform3dvEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM3DVEXTPROC glad_glProgramUniform3dvEXT = glad_on_demand_impl_glProgramUniform3dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform3fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    glad_glProgramUniform3fEXT = (PFNGLPROGRAMUNIFORM3FEXTPROC) glad_gl_on_demand_loader("glProgramUniform3fEXT");
    glad_glProgramUniform3fEXT(program, location, v0, v1, v2);
}
PFNGLPROGRAMUNIFORM3FEXTPROC glad_glProgramUniform3fEXT = glad_on_demand_impl_glProgramUniform3fEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat * value) {
    glad_glProgramUniform3fvEXT = (PFNGLPROGRAMUNIFORM3FVEXTPROC) glad_gl_on_demand_loader("glProgramUniform3fvEXT");
    glad_glProgramUniform3fvEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM3FVEXTPROC glad_glProgramUniform3fvEXT = glad_on_demand_impl_glProgramUniform3fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform3iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) {
    glad_glProgramUniform3iEXT = (PFNGLPROGRAMUNIFORM3IEXTPROC) glad_gl_on_demand_loader("glProgramUniform3iEXT");
    glad_glProgramUniform3iEXT(program, location, v0, v1, v2);
}
PFNGLPROGRAMUNIFORM3IEXTPROC glad_glProgramUniform3iEXT = glad_on_demand_impl_glProgramUniform3iEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint * value) {
    glad_glProgramUniform3ivEXT = (PFNGLPROGRAMUNIFORM3IVEXTPROC) glad_gl_on_demand_loader("glProgramUniform3ivEXT");
    glad_glProgramUniform3ivEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM3IVEXTPROC glad_glProgramUniform3ivEXT = glad_on_demand_impl_glProgramUniform3ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform3uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) {
    glad_glProgramUniform3uiEXT = (PFNGLPROGRAMUNIFORM3UIEXTPROC) glad_gl_on_demand_loader("glProgramUniform3uiEXT");
    glad_glProgramUniform3uiEXT(program, location, v0, v1, v2);
}
PFNGLPROGRAMUNIFORM3UIEXTPROC glad_glProgramUniform3uiEXT = glad_on_demand_impl_glProgramUniform3uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform3uivEXT(GLuint program, GLint location, GLsizei count, const GLuint * value) {
    glad_glProgramUniform3uivEXT = (PFNGLPROGRAMUNIFORM3UIVEXTPROC) glad_gl_on_demand_loader("glProgramUniform3uivEXT");
    glad_glProgramUniform3uivEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM3UIVEXTPROC glad_glProgramUniform3uivEXT = glad_on_demand_impl_glProgramUniform3uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform4dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glProgramUniform4dEXT = (PFNGLPROGRAMUNIFORM4DEXTPROC) glad_gl_on_demand_loader("glProgramUniform4dEXT");
    glad_glProgramUniform4dEXT(program, location, x, y, z, w);
}
PFNGLPROGRAMUNIFORM4DEXTPROC glad_glProgramUniform4dEXT = glad_on_demand_impl_glProgramUniform4dEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform4dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble * value) {
    glad_glProgramUniform4dvEXT = (PFNGLPROGRAMUNIFORM4DVEXTPROC) glad_gl_on_demand_loader("glProgramUniform4dvEXT");
    glad_glProgramUniform4dvEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM4DVEXTPROC glad_glProgramUniform4dvEXT = glad_on_demand_impl_glProgramUniform4dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform4fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glad_glProgramUniform4fEXT = (PFNGLPROGRAMUNIFORM4FEXTPROC) glad_gl_on_demand_loader("glProgramUniform4fEXT");
    glad_glProgramUniform4fEXT(program, location, v0, v1, v2, v3);
}
PFNGLPROGRAMUNIFORM4FEXTPROC glad_glProgramUniform4fEXT = glad_on_demand_impl_glProgramUniform4fEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat * value) {
    glad_glProgramUniform4fvEXT = (PFNGLPROGRAMUNIFORM4FVEXTPROC) glad_gl_on_demand_loader("glProgramUniform4fvEXT");
    glad_glProgramUniform4fvEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM4FVEXTPROC glad_glProgramUniform4fvEXT = glad_on_demand_impl_glProgramUniform4fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform4iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    glad_glProgramUniform4iEXT = (PFNGLPROGRAMUNIFORM4IEXTPROC) glad_gl_on_demand_loader("glProgramUniform4iEXT");
    glad_glProgramUniform4iEXT(program, location, v0, v1, v2, v3);
}
PFNGLPROGRAMUNIFORM4IEXTPROC glad_glProgramUniform4iEXT = glad_on_demand_impl_glProgramUniform4iEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint * value) {
    glad_glProgramUniform4ivEXT = (PFNGLPROGRAMUNIFORM4IVEXTPROC) glad_gl_on_demand_loader("glProgramUniform4ivEXT");
    glad_glProgramUniform4ivEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM4IVEXTPROC glad_glProgramUniform4ivEXT = glad_on_demand_impl_glProgramUniform4ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform4uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    glad_glProgramUniform4uiEXT = (PFNGLPROGRAMUNIFORM4UIEXTPROC) glad_gl_on_demand_loader("glProgramUniform4uiEXT");
    glad_glProgramUniform4uiEXT(program, location, v0, v1, v2, v3);
}
PFNGLPROGRAMUNIFORM4UIEXTPROC glad_glProgramUniform4uiEXT = glad_on_demand_impl_glProgramUniform4uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniform4uivEXT(GLuint program, GLint location, GLsizei count, const GLuint * value) {
    glad_glProgramUniform4uivEXT = (PFNGLPROGRAMUNIFORM4UIVEXTPROC) glad_gl_on_demand_loader("glProgramUniform4uivEXT");
    glad_glProgramUniform4uivEXT(program, location, count, value);
}
PFNGLPROGRAMUNIFORM4UIVEXTPROC glad_glProgramUniform4uivEXT = glad_on_demand_impl_glProgramUniform4uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) {
    glad_glProgramUniformMatrix2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix2dvEXT");
    glad_glProgramUniformMatrix2dvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC glad_glProgramUniformMatrix2dvEXT = glad_on_demand_impl_glProgramUniformMatrix2dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glProgramUniformMatrix2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix2fvEXT");
    glad_glProgramUniformMatrix2fvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glad_glProgramUniformMatrix2fvEXT = glad_on_demand_impl_glProgramUniformMatrix2fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix2x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) {
    glad_glProgramUniformMatrix2x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix2x3dvEXT");
    glad_glProgramUniformMatrix2x3dvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC glad_glProgramUniformMatrix2x3dvEXT = glad_on_demand_impl_glProgramUniformMatrix2x3dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix2x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glProgramUniformMatrix2x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix2x3fvEXT");
    glad_glProgramUniformMatrix2x3fvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glad_glProgramUniformMatrix2x3fvEXT = glad_on_demand_impl_glProgramUniformMatrix2x3fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix2x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) {
    glad_glProgramUniformMatrix2x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix2x4dvEXT");
    glad_glProgramUniformMatrix2x4dvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC glad_glProgramUniformMatrix2x4dvEXT = glad_on_demand_impl_glProgramUniformMatrix2x4dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix2x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glProgramUniformMatrix2x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix2x4fvEXT");
    glad_glProgramUniformMatrix2x4fvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glad_glProgramUniformMatrix2x4fvEXT = glad_on_demand_impl_glProgramUniformMatrix2x4fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) {
    glad_glProgramUniformMatrix3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix3dvEXT");
    glad_glProgramUniformMatrix3dvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC glad_glProgramUniformMatrix3dvEXT = glad_on_demand_impl_glProgramUniformMatrix3dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glProgramUniformMatrix3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix3fvEXT");
    glad_glProgramUniformMatrix3fvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glad_glProgramUniformMatrix3fvEXT = glad_on_demand_impl_glProgramUniformMatrix3fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix3x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) {
    glad_glProgramUniformMatrix3x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix3x2dvEXT");
    glad_glProgramUniformMatrix3x2dvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC glad_glProgramUniformMatrix3x2dvEXT = glad_on_demand_impl_glProgramUniformMatrix3x2dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix3x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glProgramUniformMatrix3x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix3x2fvEXT");
    glad_glProgramUniformMatrix3x2fvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glad_glProgramUniformMatrix3x2fvEXT = glad_on_demand_impl_glProgramUniformMatrix3x2fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix3x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) {
    glad_glProgramUniformMatrix3x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix3x4dvEXT");
    glad_glProgramUniformMatrix3x4dvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC glad_glProgramUniformMatrix3x4dvEXT = glad_on_demand_impl_glProgramUniformMatrix3x4dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix3x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glProgramUniformMatrix3x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix3x4fvEXT");
    glad_glProgramUniformMatrix3x4fvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glad_glProgramUniformMatrix3x4fvEXT = glad_on_demand_impl_glProgramUniformMatrix3x4fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) {
    glad_glProgramUniformMatrix4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix4dvEXT");
    glad_glProgramUniformMatrix4dvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC glad_glProgramUniformMatrix4dvEXT = glad_on_demand_impl_glProgramUniformMatrix4dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glProgramUniformMatrix4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix4fvEXT");
    glad_glProgramUniformMatrix4fvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glad_glProgramUniformMatrix4fvEXT = glad_on_demand_impl_glProgramUniformMatrix4fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix4x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) {
    glad_glProgramUniformMatrix4x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix4x2dvEXT");
    glad_glProgramUniformMatrix4x2dvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC glad_glProgramUniformMatrix4x2dvEXT = glad_on_demand_impl_glProgramUniformMatrix4x2dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix4x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glProgramUniformMatrix4x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix4x2fvEXT");
    glad_glProgramUniformMatrix4x2fvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glad_glProgramUniformMatrix4x2fvEXT = glad_on_demand_impl_glProgramUniformMatrix4x2fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix4x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) {
    glad_glProgramUniformMatrix4x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix4x3dvEXT");
    glad_glProgramUniformMatrix4x3dvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC glad_glProgramUniformMatrix4x3dvEXT = glad_on_demand_impl_glProgramUniformMatrix4x3dvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramUniformMatrix4x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glProgramUniformMatrix4x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) glad_gl_on_demand_loader("glProgramUniformMatrix4x3fvEXT");
    glad_glProgramUniformMatrix4x3fvEXT(program, location, count, transpose, value);
}
PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glad_glProgramUniformMatrix4x3fvEXT = glad_on_demand_impl_glProgramUniformMatrix4x3fvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glProgramVertexLimitNV(GLenum target, GLint limit) {
    glad_glProgramVertexLimitNV = (PFNGLPROGRAMVERTEXLIMITNVPROC) glad_gl_on_demand_loader("glProgramVertexLimitNV");
    glad_glProgramVertexLimitNV(target, limit);
}
PFNGLPROGRAMVERTEXLIMITNVPROC glad_glProgramVertexLimitNV = glad_on_demand_impl_glProgramVertexLimitNV;
static void GLAD_API_PTR glad_on_demand_impl_glProvokingVertex(GLenum mode) {
    glad_glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC) glad_gl_on_demand_loader("glProvokingVertex");
    glad_glProvokingVertex(mode);
}
PFNGLPROVOKINGVERTEXPROC glad_glProvokingVertex = glad_on_demand_impl_glProvokingVertex;
static void GLAD_API_PTR glad_on_demand_impl_glProvokingVertexEXT(GLenum mode) {
    glad_glProvokingVertexEXT = (PFNGLPROVOKINGVERTEXEXTPROC) glad_gl_on_demand_loader("glProvokingVertexEXT");
    glad_glProvokingVertexEXT(mode);
}
PFNGLPROVOKINGVERTEXEXTPROC glad_glProvokingVertexEXT = glad_on_demand_impl_glProvokingVertexEXT;
static void GLAD_API_PTR glad_on_demand_impl_glPushClientAttribDefaultEXT(GLbitfield mask) {
    glad_glPushClientAttribDefaultEXT = (PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC) glad_gl_on_demand_loader("glPushClientAttribDefaultEXT");
    glad_glPushClientAttribDefaultEXT(mask);
}
PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC glad_glPushClientAttribDefaultEXT = glad_on_demand_impl_glPushClientAttribDefaultEXT;
static void GLAD_API_PTR glad_on_demand_impl_glQueryCounter(GLuint id, GLenum target) {
    glad_glQueryCounter = (PFNGLQUERYCOUNTERPROC) glad_gl_on_demand_loader("glQueryCounter");
    glad_glQueryCounter(id, target);
}
PFNGLQUERYCOUNTERPROC glad_glQueryCounter = glad_on_demand_impl_glQueryCounter;
static void GLAD_API_PTR glad_on_demand_impl_glReadBuffer(GLenum src) {
    glad_glReadBuffer = (PFNGLREADBUFFERPROC) glad_gl_on_demand_loader("glReadBuffer");
    glad_glReadBuffer(src);
}
PFNGLREADBUFFERPROC glad_glReadBuffer = glad_on_demand_impl_glReadBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels) {
    glad_glReadPixels = (PFNGLREADPIXELSPROC) glad_gl_on_demand_loader("glReadPixels");
    glad_glReadPixels(x, y, width, height, format, type, pixels);
}
PFNGLREADPIXELSPROC glad_glReadPixels = glad_on_demand_impl_glReadPixels;
static void GLAD_API_PTR glad_on_demand_impl_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) glad_gl_on_demand_loader("glRenderbufferStorage");
    glad_glRenderbufferStorage(target, internalformat, width, height);
}
PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage = glad_on_demand_impl_glRenderbufferStorage;
static void GLAD_API_PTR glad_on_demand_impl_glRenderbufferStorageEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC) glad_gl_on_demand_loader("glRenderbufferStorageEXT");
    glad_glRenderbufferStorageEXT(target, internalformat, width, height);
}
PFNGLRENDERBUFFERSTORAGEEXTPROC glad_glRenderbufferStorageEXT = glad_on_demand_impl_glRenderbufferStorageEXT;
static void GLAD_API_PTR glad_on_demand_impl_glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) glad_gl_on_demand_loader("glRenderbufferStorageMultisample");
    glad_glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glRenderbufferStorageMultisample = glad_on_demand_impl_glRenderbufferStorageMultisample;
static void GLAD_API_PTR glad_on_demand_impl_glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) glad_gl_on_demand_loader("glRenderbufferStorageMultisampleEXT");
    glad_glRenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height);
}
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glad_glRenderbufferStorageMultisampleEXT = glad_on_demand_impl_glRenderbufferStorageMultisampleEXT;
static void GLAD_API_PTR glad_on_demand_impl_glRequestResidentProgramsNV(GLsizei n, const GLuint * programs) {
    glad_glRequestResidentProgramsNV = (PFNGLREQUESTRESIDENTPROGRAMSNVPROC) glad_gl_on_demand_loader("glRequestResidentProgramsNV");
    glad_glRequestResidentProgramsNV(n, programs);
}
PFNGLREQUESTRESIDENTPROGRAMSNVPROC glad_glRequestResidentProgramsNV = glad_on_demand_impl_glRequestResidentProgramsNV;
static void GLAD_API_PTR glad_on_demand_impl_glSampleCoverage(GLfloat value, GLboolean invert) {
    glad_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) glad_gl_on_demand_loader("glSampleCoverage");
    glad_glSampleCoverage(value, invert);
}
PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage = glad_on_demand_impl_glSampleCoverage;
static void GLAD_API_PTR glad_on_demand_impl_glSampleCoverageARB(GLfloat value, GLboolean invert) {
    glad_glSampleCoverageARB = (PFNGLSAMPLECOVERAGEARBPROC) glad_gl_on_demand_loader("glSampleCoverageARB");
    glad_glSampleCoverageARB(value, invert);
}
PFNGLSAMPLECOVERAGEARBPROC glad_glSampleCoverageARB = glad_on_demand_impl_glSampleCoverageARB;
static void GLAD_API_PTR glad_on_demand_impl_glSampleMaskIndexedNV(GLuint index, GLbitfield mask) {
    glad_glSampleMaskIndexedNV = (PFNGLSAMPLEMASKINDEXEDNVPROC) glad_gl_on_demand_loader("glSampleMaskIndexedNV");
    glad_glSampleMaskIndexedNV(index, mask);
}
PFNGLSAMPLEMASKINDEXEDNVPROC glad_glSampleMaskIndexedNV = glad_on_demand_impl_glSampleMaskIndexedNV;
static void GLAD_API_PTR glad_on_demand_impl_glSampleMaski(GLuint maskNumber, GLbitfield mask) {
    glad_glSampleMaski = (PFNGLSAMPLEMASKIPROC) glad_gl_on_demand_loader("glSampleMaski");
    glad_glSampleMaski(maskNumber, mask);
}
PFNGLSAMPLEMASKIPROC glad_glSampleMaski = glad_on_demand_impl_glSampleMaski;
static void GLAD_API_PTR glad_on_demand_impl_glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param) {
    glad_glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC) glad_gl_on_demand_loader("glSamplerParameterIiv");
    glad_glSamplerParameterIiv(sampler, pname, param);
}
PFNGLSAMPLERPARAMETERIIVPROC glad_glSamplerParameterIiv = glad_on_demand_impl_glSamplerParameterIiv;
static void GLAD_API_PTR glad_on_demand_impl_glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param) {
    glad_glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC) glad_gl_on_demand_loader("glSamplerParameterIuiv");
    glad_glSamplerParameterIuiv(sampler, pname, param);
}
PFNGLSAMPLERPARAMETERIUIVPROC glad_glSamplerParameterIuiv = glad_on_demand_impl_glSamplerParameterIuiv;
static void GLAD_API_PTR glad_on_demand_impl_glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) {
    glad_glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC) glad_gl_on_demand_loader("glSamplerParameterf");
    glad_glSamplerParameterf(sampler, pname, param);
}
PFNGLSAMPLERPARAMETERFPROC glad_glSamplerParameterf = glad_on_demand_impl_glSamplerParameterf;
static void GLAD_API_PTR glad_on_demand_impl_glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param) {
    glad_glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC) glad_gl_on_demand_loader("glSamplerParameterfv");
    glad_glSamplerParameterfv(sampler, pname, param);
}
PFNGLSAMPLERPARAMETERFVPROC glad_glSamplerParameterfv = glad_on_demand_impl_glSamplerParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glSamplerParameteri(GLuint sampler, GLenum pname, GLint param) {
    glad_glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC) glad_gl_on_demand_loader("glSamplerParameteri");
    glad_glSamplerParameteri(sampler, pname, param);
}
PFNGLSAMPLERPARAMETERIPROC glad_glSamplerParameteri = glad_on_demand_impl_glSamplerParameteri;
static void GLAD_API_PTR glad_on_demand_impl_glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param) {
    glad_glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC) glad_gl_on_demand_loader("glSamplerParameteriv");
    glad_glSamplerParameteriv(sampler, pname, param);
}
PFNGLSAMPLERPARAMETERIVPROC glad_glSamplerParameteriv = glad_on_demand_impl_glSamplerParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glScissor = (PFNGLSCISSORPROC) glad_gl_on_demand_loader("glScissor");
    glad_glScissor(x, y, width, height);
}
PFNGLSCISSORPROC glad_glScissor = glad_on_demand_impl_glScissor;
static void GLAD_API_PTR glad_on_demand_impl_glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length) {
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC) glad_gl_on_demand_loader("glShaderSource");
    glad_glShaderSource(shader, count, string, length);
}
PFNGLSHADERSOURCEPROC glad_glShaderSource = glad_on_demand_impl_glShaderSource;
static void GLAD_API_PTR glad_on_demand_impl_glShaderSourceARB(GLhandleARB shaderObj, GLsizei count, const GLcharARB ** string, const GLint * length) {
    glad_glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) glad_gl_on_demand_loader("glShaderSourceARB");
    glad_glShaderSourceARB(shaderObj, count, string, length);
}
PFNGLSHADERSOURCEARBPROC glad_glShaderSourceARB = glad_on_demand_impl_glShaderSourceARB;
static void GLAD_API_PTR glad_on_demand_impl_glStencilFunc(GLenum func, GLint ref, GLuint mask) {
    glad_glStencilFunc = (PFNGLSTENCILFUNCPROC) glad_gl_on_demand_loader("glStencilFunc");
    glad_glStencilFunc(func, ref, mask);
}
PFNGLSTENCILFUNCPROC glad_glStencilFunc = glad_on_demand_impl_glStencilFunc;
static void GLAD_API_PTR glad_on_demand_impl_glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
    glad_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC) glad_gl_on_demand_loader("glStencilFuncSeparate");
    glad_glStencilFuncSeparate(face, func, ref, mask);
}
PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate = glad_on_demand_impl_glStencilFuncSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glStencilFuncSeparateATI(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask) {
    glad_glStencilFuncSeparateATI = (PFNGLSTENCILFUNCSEPARATEATIPROC) glad_gl_on_demand_loader("glStencilFuncSeparateATI");
    glad_glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask);
}
PFNGLSTENCILFUNCSEPARATEATIPROC glad_glStencilFuncSeparateATI = glad_on_demand_impl_glStencilFuncSeparateATI;
static void GLAD_API_PTR glad_on_demand_impl_glStencilMask(GLuint mask) {
    glad_glStencilMask = (PFNGLSTENCILMASKPROC) glad_gl_on_demand_loader("glStencilMask");
    glad_glStencilMask(mask);
}
PFNGLSTENCILMASKPROC glad_glStencilMask = glad_on_demand_impl_glStencilMask;
static void GLAD_API_PTR glad_on_demand_impl_glStencilMaskSeparate(GLenum face, GLuint mask) {
    glad_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC) glad_gl_on_demand_loader("glStencilMaskSeparate");
    glad_glStencilMaskSeparate(face, mask);
}
PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate = glad_on_demand_impl_glStencilMaskSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
    glad_glStencilOp = (PFNGLSTENCILOPPROC) glad_gl_on_demand_loader("glStencilOp");
    glad_glStencilOp(fail, zfail, zpass);
}
PFNGLSTENCILOPPROC glad_glStencilOp = glad_on_demand_impl_glStencilOp;
static void GLAD_API_PTR glad_on_demand_impl_glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    glad_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC) glad_gl_on_demand_loader("glStencilOpSeparate");
    glad_glStencilOpSeparate(face, sfail, dpfail, dppass);
}
PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate = glad_on_demand_impl_glStencilOpSeparate;
static void GLAD_API_PTR glad_on_demand_impl_glStencilOpSeparateATI(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    glad_glStencilOpSeparateATI = (PFNGLSTENCILOPSEPARATEATIPROC) glad_gl_on_demand_loader("glStencilOpSeparateATI");
    glad_glStencilOpSeparateATI(face, sfail, dpfail, dppass);
}
PFNGLSTENCILOPSEPARATEATIPROC glad_glStencilOpSeparateATI = glad_on_demand_impl_glStencilOpSeparateATI;
static void GLAD_API_PTR glad_on_demand_impl_glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer) {
    glad_glTexBuffer = (PFNGLTEXBUFFERPROC) glad_gl_on_demand_loader("glTexBuffer");
    glad_glTexBuffer(target, internalformat, buffer);
}
PFNGLTEXBUFFERPROC glad_glTexBuffer = glad_on_demand_impl_glTexBuffer;
static void GLAD_API_PTR glad_on_demand_impl_glTexBufferARB(GLenum target, GLenum internalformat, GLuint buffer) {
    glad_glTexBufferARB = (PFNGLTEXBUFFERARBPROC) glad_gl_on_demand_loader("glTexBufferARB");
    glad_glTexBufferARB(target, internalformat, buffer);
}
PFNGLTEXBUFFERARBPROC glad_glTexBufferARB = glad_on_demand_impl_glTexBufferARB;
static void GLAD_API_PTR glad_on_demand_impl_glTexBufferEXT(GLenum target, GLenum internalformat, GLuint buffer) {
    glad_glTexBufferEXT = (PFNGLTEXBUFFEREXTPROC) glad_gl_on_demand_loader("glTexBufferEXT");
    glad_glTexBufferEXT(target, internalformat, buffer);
}
PFNGLTEXBUFFEREXTPROC glad_glTexBufferEXT = glad_on_demand_impl_glTexBufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTexCoordPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void * pointer) {
    glad_glTexCoordPointerEXT = (PFNGLTEXCOORDPOINTEREXTPROC) glad_gl_on_demand_loader("glTexCoordPointerEXT");
    glad_glTexCoordPointerEXT(size, type, stride, count, pointer);
}
PFNGLTEXCOORDPOINTEREXTPROC glad_glTexCoordPointerEXT = glad_on_demand_impl_glTexCoordPointerEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTexImage1D = (PFNGLTEXIMAGE1DPROC) glad_gl_on_demand_loader("glTexImage1D");
    glad_glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
}
PFNGLTEXIMAGE1DPROC glad_glTexImage1D = glad_on_demand_impl_glTexImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC) glad_gl_on_demand_loader("glTexImage2D");
    glad_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = glad_on_demand_impl_glTexImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
    glad_glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC) glad_gl_on_demand_loader("glTexImage2DMultisample");
    glad_glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}
PFNGLTEXIMAGE2DMULTISAMPLEPROC glad_glTexImage2DMultisample = glad_on_demand_impl_glTexImage2DMultisample;
static void GLAD_API_PTR glad_on_demand_impl_glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTexImage3D = (PFNGLTEXIMAGE3DPROC) glad_gl_on_demand_loader("glTexImage3D");
    glad_glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}
PFNGLTEXIMAGE3DPROC glad_glTexImage3D = glad_on_demand_impl_glTexImage3D;
static void GLAD_API_PTR glad_on_demand_impl_glTexImage3DEXT(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTexImage3DEXT = (PFNGLTEXIMAGE3DEXTPROC) glad_gl_on_demand_loader("glTexImage3DEXT");
    glad_glTexImage3DEXT(target, level, internalformat, width, height, depth, border, format, type, pixels);
}
PFNGLTEXIMAGE3DEXTPROC glad_glTexImage3DEXT = glad_on_demand_impl_glTexImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {
    glad_glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC) glad_gl_on_demand_loader("glTexImage3DMultisample");
    glad_glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}
PFNGLTEXIMAGE3DMULTISAMPLEPROC glad_glTexImage3DMultisample = glad_on_demand_impl_glTexImage3DMultisample;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterIiv(GLenum target, GLenum pname, const GLint * params) {
    glad_glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC) glad_gl_on_demand_loader("glTexParameterIiv");
    glad_glTexParameterIiv(target, pname, params);
}
PFNGLTEXPARAMETERIIVPROC glad_glTexParameterIiv = glad_on_demand_impl_glTexParameterIiv;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterIivEXT(GLenum target, GLenum pname, const GLint * params) {
    glad_glTexParameterIivEXT = (PFNGLTEXPARAMETERIIVEXTPROC) glad_gl_on_demand_loader("glTexParameterIivEXT");
    glad_glTexParameterIivEXT(target, pname, params);
}
PFNGLTEXPARAMETERIIVEXTPROC glad_glTexParameterIivEXT = glad_on_demand_impl_glTexParameterIivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterIuiv(GLenum target, GLenum pname, const GLuint * params) {
    glad_glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC) glad_gl_on_demand_loader("glTexParameterIuiv");
    glad_glTexParameterIuiv(target, pname, params);
}
PFNGLTEXPARAMETERIUIVPROC glad_glTexParameterIuiv = glad_on_demand_impl_glTexParameterIuiv;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterIuivEXT(GLenum target, GLenum pname, const GLuint * params) {
    glad_glTexParameterIuivEXT = (PFNGLTEXPARAMETERIUIVEXTPROC) glad_gl_on_demand_loader("glTexParameterIuivEXT");
    glad_glTexParameterIuivEXT(target, pname, params);
}
PFNGLTEXPARAMETERIUIVEXTPROC glad_glTexParameterIuivEXT = glad_on_demand_impl_glTexParameterIuivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
    glad_glTexParameterf = (PFNGLTEXPARAMETERFPROC) glad_gl_on_demand_loader("glTexParameterf");
    glad_glTexParameterf(target, pname, param);
}
PFNGLTEXPARAMETERFPROC glad_glTexParameterf = glad_on_demand_impl_glTexParameterf;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameterfv(GLenum target, GLenum pname, const GLfloat * params) {
    glad_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC) glad_gl_on_demand_loader("glTexParameterfv");
    glad_glTexParameterfv(target, pname, params);
}
PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv = glad_on_demand_impl_glTexParameterfv;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameteri(GLenum target, GLenum pname, GLint param) {
    glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC) glad_gl_on_demand_loader("glTexParameteri");
    glad_glTexParameteri(target, pname, param);
}
PFNGLTEXPARAMETERIPROC glad_glTexParameteri = glad_on_demand_impl_glTexParameteri;
static void GLAD_API_PTR glad_on_demand_impl_glTexParameteriv(GLenum target, GLenum pname, const GLint * params) {
    glad_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC) glad_gl_on_demand_loader("glTexParameteriv");
    glad_glTexParameteriv(target, pname, params);
}
PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv = glad_on_demand_impl_glTexParameteriv;
static void GLAD_API_PTR glad_on_demand_impl_glTexRenderbufferNV(GLenum target, GLuint renderbuffer) {
    glad_glTexRenderbufferNV = (PFNGLTEXRENDERBUFFERNVPROC) glad_gl_on_demand_loader("glTexRenderbufferNV");
    glad_glTexRenderbufferNV(target, renderbuffer);
}
PFNGLTEXRENDERBUFFERNVPROC glad_glTexRenderbufferNV = glad_on_demand_impl_glTexRenderbufferNV;
static void GLAD_API_PTR glad_on_demand_impl_glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels) {
    glad_glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC) glad_gl_on_demand_loader("glTexSubImage1D");
    glad_glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}
PFNGLTEXSUBIMAGE1DPROC glad_glTexSubImage1D = glad_on_demand_impl_glTexSubImage1D;
static void GLAD_API_PTR glad_on_demand_impl_glTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels) {
    glad_glTexSubImage1DEXT = (PFNGLTEXSUBIMAGE1DEXTPROC) glad_gl_on_demand_loader("glTexSubImage1DEXT");
    glad_glTexSubImage1DEXT(target, level, xoffset, width, format, type, pixels);
}
PFNGLTEXSUBIMAGE1DEXTPROC glad_glTexSubImage1DEXT = glad_on_demand_impl_glTexSubImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) {
    glad_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) glad_gl_on_demand_loader("glTexSubImage2D");
    glad_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}
PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D = glad_on_demand_impl_glTexSubImage2D;
static void GLAD_API_PTR glad_on_demand_impl_glTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) {
    glad_glTexSubImage2DEXT = (PFNGLTEXSUBIMAGE2DEXTPROC) glad_gl_on_demand_loader("glTexSubImage2DEXT");
    glad_glTexSubImage2DEXT(target, level, xoffset, yoffset, width, height, format, type, pixels);
}
PFNGLTEXSUBIMAGE2DEXTPROC glad_glTexSubImage2DEXT = glad_on_demand_impl_glTexSubImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels) {
    glad_glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) glad_gl_on_demand_loader("glTexSubImage3D");
    glad_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}
PFNGLTEXSUBIMAGE3DPROC glad_glTexSubImage3D = glad_on_demand_impl_glTexSubImage3D;
static void GLAD_API_PTR glad_on_demand_impl_glTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels) {
    glad_glTexSubImage3DEXT = (PFNGLTEXSUBIMAGE3DEXTPROC) glad_gl_on_demand_loader("glTexSubImage3DEXT");
    glad_glTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}
PFNGLTEXSUBIMAGE3DEXTPROC glad_glTexSubImage3DEXT = glad_on_demand_impl_glTexSubImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureBufferEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer) {
    glad_glTextureBufferEXT = (PFNGLTEXTUREBUFFEREXTPROC) glad_gl_on_demand_loader("glTextureBufferEXT");
    glad_glTextureBufferEXT(texture, target, internalformat, buffer);
}
PFNGLTEXTUREBUFFEREXTPROC glad_glTextureBufferEXT = glad_on_demand_impl_glTextureBufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureBufferRangeEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    glad_glTextureBufferRangeEXT = (PFNGLTEXTUREBUFFERRANGEEXTPROC) glad_gl_on_demand_loader("glTextureBufferRangeEXT");
    glad_glTextureBufferRangeEXT(texture, target, internalformat, buffer, offset, size);
}
PFNGLTEXTUREBUFFERRANGEEXTPROC glad_glTextureBufferRangeEXT = glad_on_demand_impl_glTextureBufferRangeEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTextureImage1DEXT = (PFNGLTEXTUREIMAGE1DEXTPROC) glad_gl_on_demand_loader("glTextureImage1DEXT");
    glad_glTextureImage1DEXT(texture, target, level, internalformat, width, border, format, type, pixels);
}
PFNGLTEXTUREIMAGE1DEXTPROC glad_glTextureImage1DEXT = glad_on_demand_impl_glTextureImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTextureImage2DEXT = (PFNGLTEXTUREIMAGE2DEXTPROC) glad_gl_on_demand_loader("glTextureImage2DEXT");
    glad_glTextureImage2DEXT(texture, target, level, internalformat, width, height, border, format, type, pixels);
}
PFNGLTEXTUREIMAGE2DEXTPROC glad_glTextureImage2DEXT = glad_on_demand_impl_glTextureImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels) {
    glad_glTextureImage3DEXT = (PFNGLTEXTUREIMAGE3DEXTPROC) glad_gl_on_demand_loader("glTextureImage3DEXT");
    glad_glTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, format, type, pixels);
}
PFNGLTEXTUREIMAGE3DEXTPROC glad_glTextureImage3DEXT = glad_on_demand_impl_glTextureImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTexturePageCommitmentEXT(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit) {
    glad_glTexturePageCommitmentEXT = (PFNGLTEXTUREPAGECOMMITMENTEXTPROC) glad_gl_on_demand_loader("glTexturePageCommitmentEXT");
    glad_glTexturePageCommitmentEXT(texture, level, xoffset, yoffset, zoffset, width, height, depth, commit);
}
PFNGLTEXTUREPAGECOMMITMENTEXTPROC glad_glTexturePageCommitmentEXT = glad_on_demand_impl_glTexturePageCommitmentEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, const GLint * params) {
    glad_glTextureParameterIivEXT = (PFNGLTEXTUREPARAMETERIIVEXTPROC) glad_gl_on_demand_loader("glTextureParameterIivEXT");
    glad_glTextureParameterIivEXT(texture, target, pname, params);
}
PFNGLTEXTUREPARAMETERIIVEXTPROC glad_glTextureParameterIivEXT = glad_on_demand_impl_glTextureParameterIivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, const GLuint * params) {
    glad_glTextureParameterIuivEXT = (PFNGLTEXTUREPARAMETERIUIVEXTPROC) glad_gl_on_demand_loader("glTextureParameterIuivEXT");
    glad_glTextureParameterIuivEXT(texture, target, pname, params);
}
PFNGLTEXTUREPARAMETERIUIVEXTPROC glad_glTextureParameterIuivEXT = glad_on_demand_impl_glTextureParameterIuivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureParameterfEXT(GLuint texture, GLenum target, GLenum pname, GLfloat param) {
    glad_glTextureParameterfEXT = (PFNGLTEXTUREPARAMETERFEXTPROC) glad_gl_on_demand_loader("glTextureParameterfEXT");
    glad_glTextureParameterfEXT(texture, target, pname, param);
}
PFNGLTEXTUREPARAMETERFEXTPROC glad_glTextureParameterfEXT = glad_on_demand_impl_glTextureParameterfEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, const GLfloat * params) {
    glad_glTextureParameterfvEXT = (PFNGLTEXTUREPARAMETERFVEXTPROC) glad_gl_on_demand_loader("glTextureParameterfvEXT");
    glad_glTextureParameterfvEXT(texture, target, pname, params);
}
PFNGLTEXTUREPARAMETERFVEXTPROC glad_glTextureParameterfvEXT = glad_on_demand_impl_glTextureParameterfvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureParameteriEXT(GLuint texture, GLenum target, GLenum pname, GLint param) {
    glad_glTextureParameteriEXT = (PFNGLTEXTUREPARAMETERIEXTPROC) glad_gl_on_demand_loader("glTextureParameteriEXT");
    glad_glTextureParameteriEXT(texture, target, pname, param);
}
PFNGLTEXTUREPARAMETERIEXTPROC glad_glTextureParameteriEXT = glad_on_demand_impl_glTextureParameteriEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, const GLint * params) {
    glad_glTextureParameterivEXT = (PFNGLTEXTUREPARAMETERIVEXTPROC) glad_gl_on_demand_loader("glTextureParameterivEXT");
    glad_glTextureParameterivEXT(texture, target, pname, params);
}
PFNGLTEXTUREPARAMETERIVEXTPROC glad_glTextureParameterivEXT = glad_on_demand_impl_glTextureParameterivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureRenderbufferEXT(GLuint texture, GLenum target, GLuint renderbuffer) {
    glad_glTextureRenderbufferEXT = (PFNGLTEXTURERENDERBUFFEREXTPROC) glad_gl_on_demand_loader("glTextureRenderbufferEXT");
    glad_glTextureRenderbufferEXT(texture, target, renderbuffer);
}
PFNGLTEXTURERENDERBUFFEREXTPROC glad_glTextureRenderbufferEXT = glad_on_demand_impl_glTextureRenderbufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) {
    glad_glTextureStorage1DEXT = (PFNGLTEXTURESTORAGE1DEXTPROC) glad_gl_on_demand_loader("glTextureStorage1DEXT");
    glad_glTextureStorage1DEXT(texture, target, levels, internalformat, width);
}
PFNGLTEXTURESTORAGE1DEXTPROC glad_glTextureStorage1DEXT = glad_on_demand_impl_glTextureStorage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) {
    glad_glTextureStorage2DEXT = (PFNGLTEXTURESTORAGE2DEXTPROC) glad_gl_on_demand_loader("glTextureStorage2DEXT");
    glad_glTextureStorage2DEXT(texture, target, levels, internalformat, width, height);
}
PFNGLTEXTURESTORAGE2DEXTPROC glad_glTextureStorage2DEXT = glad_on_demand_impl_glTextureStorage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureStorage2DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
    glad_glTextureStorage2DMultisampleEXT = (PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC) glad_gl_on_demand_loader("glTextureStorage2DMultisampleEXT");
    glad_glTextureStorage2DMultisampleEXT(texture, target, samples, internalformat, width, height, fixedsamplelocations);
}
PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC glad_glTextureStorage2DMultisampleEXT = glad_on_demand_impl_glTextureStorage2DMultisampleEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) {
    glad_glTextureStorage3DEXT = (PFNGLTEXTURESTORAGE3DEXTPROC) glad_gl_on_demand_loader("glTextureStorage3DEXT");
    glad_glTextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth);
}
PFNGLTEXTURESTORAGE3DEXTPROC glad_glTextureStorage3DEXT = glad_on_demand_impl_glTextureStorage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureStorage3DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {
    glad_glTextureStorage3DMultisampleEXT = (PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC) glad_gl_on_demand_loader("glTextureStorage3DMultisampleEXT");
    glad_glTextureStorage3DMultisampleEXT(texture, target, samples, internalformat, width, height, depth, fixedsamplelocations);
}
PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC glad_glTextureStorage3DMultisampleEXT = glad_on_demand_impl_glTextureStorage3DMultisampleEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels) {
    glad_glTextureSubImage1DEXT = (PFNGLTEXTURESUBIMAGE1DEXTPROC) glad_gl_on_demand_loader("glTextureSubImage1DEXT");
    glad_glTextureSubImage1DEXT(texture, target, level, xoffset, width, format, type, pixels);
}
PFNGLTEXTURESUBIMAGE1DEXTPROC glad_glTextureSubImage1DEXT = glad_on_demand_impl_glTextureSubImage1DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) {
    glad_glTextureSubImage2DEXT = (PFNGLTEXTURESUBIMAGE2DEXTPROC) glad_gl_on_demand_loader("glTextureSubImage2DEXT");
    glad_glTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, type, pixels);
}
PFNGLTEXTURESUBIMAGE2DEXTPROC glad_glTextureSubImage2DEXT = glad_on_demand_impl_glTextureSubImage2DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels) {
    glad_glTextureSubImage3DEXT = (PFNGLTEXTURESUBIMAGE3DEXTPROC) glad_gl_on_demand_loader("glTextureSubImage3DEXT");
    glad_glTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}
PFNGLTEXTURESUBIMAGE3DEXTPROC glad_glTextureSubImage3DEXT = glad_on_demand_impl_glTextureSubImage3DEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTrackMatrixNV(GLenum target, GLuint address, GLenum matrix, GLenum transform) {
    glad_glTrackMatrixNV = (PFNGLTRACKMATRIXNVPROC) glad_gl_on_demand_loader("glTrackMatrixNV");
    glad_glTrackMatrixNV(target, address, matrix, transform);
}
PFNGLTRACKMATRIXNVPROC glad_glTrackMatrixNV = glad_on_demand_impl_glTrackMatrixNV;
static void GLAD_API_PTR glad_on_demand_impl_glTransformFeedbackAttribsNV(GLsizei count, const GLint * attribs, GLenum bufferMode) {
    glad_glTransformFeedbackAttribsNV = (PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC) glad_gl_on_demand_loader("glTransformFeedbackAttribsNV");
    glad_glTransformFeedbackAttribsNV(count, attribs, bufferMode);
}
PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC glad_glTransformFeedbackAttribsNV = glad_on_demand_impl_glTransformFeedbackAttribsNV;
static void GLAD_API_PTR glad_on_demand_impl_glTransformFeedbackStreamAttribsNV(GLsizei count, const GLint * attribs, GLsizei nbuffers, const GLint * bufstreams, GLenum bufferMode) {
    glad_glTransformFeedbackStreamAttribsNV = (PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC) glad_gl_on_demand_loader("glTransformFeedbackStreamAttribsNV");
    glad_glTransformFeedbackStreamAttribsNV(count, attribs, nbuffers, bufstreams, bufferMode);
}
PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC glad_glTransformFeedbackStreamAttribsNV = glad_on_demand_impl_glTransformFeedbackStreamAttribsNV;
static void GLAD_API_PTR glad_on_demand_impl_glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode) {
    glad_glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC) glad_gl_on_demand_loader("glTransformFeedbackVaryings");
    glad_glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_glTransformFeedbackVaryings = glad_on_demand_impl_glTransformFeedbackVaryings;
static void GLAD_API_PTR glad_on_demand_impl_glTransformFeedbackVaryingsEXT(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode) {
    glad_glTransformFeedbackVaryingsEXT = (PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC) glad_gl_on_demand_loader("glTransformFeedbackVaryingsEXT");
    glad_glTransformFeedbackVaryingsEXT(program, count, varyings, bufferMode);
}
PFNGLTRANSFORMFEEDBACKVARYINGSEXTPROC glad_glTransformFeedbackVaryingsEXT = glad_on_demand_impl_glTransformFeedbackVaryingsEXT;
static void GLAD_API_PTR glad_on_demand_impl_glTransformFeedbackVaryingsNV(GLuint program, GLsizei count, const GLint * locations, GLenum bufferMode) {
    glad_glTransformFeedbackVaryingsNV = (PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC) glad_gl_on_demand_loader("glTransformFeedbackVaryingsNV");
    glad_glTransformFeedbackVaryingsNV(program, count, locations, bufferMode);
}
PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC glad_glTransformFeedbackVaryingsNV = glad_on_demand_impl_glTransformFeedbackVaryingsNV;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1f(GLint location, GLfloat v0) {
    glad_glUniform1f = (PFNGLUNIFORM1FPROC) glad_gl_on_demand_loader("glUniform1f");
    glad_glUniform1f(location, v0);
}
PFNGLUNIFORM1FPROC glad_glUniform1f = glad_on_demand_impl_glUniform1f;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1fARB(GLint location, GLfloat v0) {
    glad_glUniform1fARB = (PFNGLUNIFORM1FARBPROC) glad_gl_on_demand_loader("glUniform1fARB");
    glad_glUniform1fARB(location, v0);
}
PFNGLUNIFORM1FARBPROC glad_glUniform1fARB = glad_on_demand_impl_glUniform1fARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1fv(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform1fv = (PFNGLUNIFORM1FVPROC) glad_gl_on_demand_loader("glUniform1fv");
    glad_glUniform1fv(location, count, value);
}
PFNGLUNIFORM1FVPROC glad_glUniform1fv = glad_on_demand_impl_glUniform1fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1fvARB(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform1fvARB = (PFNGLUNIFORM1FVARBPROC) glad_gl_on_demand_loader("glUniform1fvARB");
    glad_glUniform1fvARB(location, count, value);
}
PFNGLUNIFORM1FVARBPROC glad_glUniform1fvARB = glad_on_demand_impl_glUniform1fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1i(GLint location, GLint v0) {
    glad_glUniform1i = (PFNGLUNIFORM1IPROC) glad_gl_on_demand_loader("glUniform1i");
    glad_glUniform1i(location, v0);
}
PFNGLUNIFORM1IPROC glad_glUniform1i = glad_on_demand_impl_glUniform1i;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1iARB(GLint location, GLint v0) {
    glad_glUniform1iARB = (PFNGLUNIFORM1IARBPROC) glad_gl_on_demand_loader("glUniform1iARB");
    glad_glUniform1iARB(location, v0);
}
PFNGLUNIFORM1IARBPROC glad_glUniform1iARB = glad_on_demand_impl_glUniform1iARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1iv(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform1iv = (PFNGLUNIFORM1IVPROC) glad_gl_on_demand_loader("glUniform1iv");
    glad_glUniform1iv(location, count, value);
}
PFNGLUNIFORM1IVPROC glad_glUniform1iv = glad_on_demand_impl_glUniform1iv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1ivARB(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform1ivARB = (PFNGLUNIFORM1IVARBPROC) glad_gl_on_demand_loader("glUniform1ivARB");
    glad_glUniform1ivARB(location, count, value);
}
PFNGLUNIFORM1IVARBPROC glad_glUniform1ivARB = glad_on_demand_impl_glUniform1ivARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1ui(GLint location, GLuint v0) {
    glad_glUniform1ui = (PFNGLUNIFORM1UIPROC) glad_gl_on_demand_loader("glUniform1ui");
    glad_glUniform1ui(location, v0);
}
PFNGLUNIFORM1UIPROC glad_glUniform1ui = glad_on_demand_impl_glUniform1ui;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1uiEXT(GLint location, GLuint v0) {
    glad_glUniform1uiEXT = (PFNGLUNIFORM1UIEXTPROC) glad_gl_on_demand_loader("glUniform1uiEXT");
    glad_glUniform1uiEXT(location, v0);
}
PFNGLUNIFORM1UIEXTPROC glad_glUniform1uiEXT = glad_on_demand_impl_glUniform1uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1uiv(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform1uiv = (PFNGLUNIFORM1UIVPROC) glad_gl_on_demand_loader("glUniform1uiv");
    glad_glUniform1uiv(location, count, value);
}
PFNGLUNIFORM1UIVPROC glad_glUniform1uiv = glad_on_demand_impl_glUniform1uiv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform1uivEXT(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform1uivEXT = (PFNGLUNIFORM1UIVEXTPROC) glad_gl_on_demand_loader("glUniform1uivEXT");
    glad_glUniform1uivEXT(location, count, value);
}
PFNGLUNIFORM1UIVEXTPROC glad_glUniform1uivEXT = glad_on_demand_impl_glUniform1uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2f(GLint location, GLfloat v0, GLfloat v1) {
    glad_glUniform2f = (PFNGLUNIFORM2FPROC) glad_gl_on_demand_loader("glUniform2f");
    glad_glUniform2f(location, v0, v1);
}
PFNGLUNIFORM2FPROC glad_glUniform2f = glad_on_demand_impl_glUniform2f;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2fARB(GLint location, GLfloat v0, GLfloat v1) {
    glad_glUniform2fARB = (PFNGLUNIFORM2FARBPROC) glad_gl_on_demand_loader("glUniform2fARB");
    glad_glUniform2fARB(location, v0, v1);
}
PFNGLUNIFORM2FARBPROC glad_glUniform2fARB = glad_on_demand_impl_glUniform2fARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2fv(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform2fv = (PFNGLUNIFORM2FVPROC) glad_gl_on_demand_loader("glUniform2fv");
    glad_glUniform2fv(location, count, value);
}
PFNGLUNIFORM2FVPROC glad_glUniform2fv = glad_on_demand_impl_glUniform2fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2fvARB(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform2fvARB = (PFNGLUNIFORM2FVARBPROC) glad_gl_on_demand_loader("glUniform2fvARB");
    glad_glUniform2fvARB(location, count, value);
}
PFNGLUNIFORM2FVARBPROC glad_glUniform2fvARB = glad_on_demand_impl_glUniform2fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2i(GLint location, GLint v0, GLint v1) {
    glad_glUniform2i = (PFNGLUNIFORM2IPROC) glad_gl_on_demand_loader("glUniform2i");
    glad_glUniform2i(location, v0, v1);
}
PFNGLUNIFORM2IPROC glad_glUniform2i = glad_on_demand_impl_glUniform2i;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2iARB(GLint location, GLint v0, GLint v1) {
    glad_glUniform2iARB = (PFNGLUNIFORM2IARBPROC) glad_gl_on_demand_loader("glUniform2iARB");
    glad_glUniform2iARB(location, v0, v1);
}
PFNGLUNIFORM2IARBPROC glad_glUniform2iARB = glad_on_demand_impl_glUniform2iARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2iv(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform2iv = (PFNGLUNIFORM2IVPROC) glad_gl_on_demand_loader("glUniform2iv");
    glad_glUniform2iv(location, count, value);
}
PFNGLUNIFORM2IVPROC glad_glUniform2iv = glad_on_demand_impl_glUniform2iv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2ivARB(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform2ivARB = (PFNGLUNIFORM2IVARBPROC) glad_gl_on_demand_loader("glUniform2ivARB");
    glad_glUniform2ivARB(location, count, value);
}
PFNGLUNIFORM2IVARBPROC glad_glUniform2ivARB = glad_on_demand_impl_glUniform2ivARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2ui(GLint location, GLuint v0, GLuint v1) {
    glad_glUniform2ui = (PFNGLUNIFORM2UIPROC) glad_gl_on_demand_loader("glUniform2ui");
    glad_glUniform2ui(location, v0, v1);
}
PFNGLUNIFORM2UIPROC glad_glUniform2ui = glad_on_demand_impl_glUniform2ui;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2uiEXT(GLint location, GLuint v0, GLuint v1) {
    glad_glUniform2uiEXT = (PFNGLUNIFORM2UIEXTPROC) glad_gl_on_demand_loader("glUniform2uiEXT");
    glad_glUniform2uiEXT(location, v0, v1);
}
PFNGLUNIFORM2UIEXTPROC glad_glUniform2uiEXT = glad_on_demand_impl_glUniform2uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2uiv(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform2uiv = (PFNGLUNIFORM2UIVPROC) glad_gl_on_demand_loader("glUniform2uiv");
    glad_glUniform2uiv(location, count, value);
}
PFNGLUNIFORM2UIVPROC glad_glUniform2uiv = glad_on_demand_impl_glUniform2uiv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform2uivEXT(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform2uivEXT = (PFNGLUNIFORM2UIVEXTPROC) glad_gl_on_demand_loader("glUniform2uivEXT");
    glad_glUniform2uivEXT(location, count, value);
}
PFNGLUNIFORM2UIVEXTPROC glad_glUniform2uivEXT = glad_on_demand_impl_glUniform2uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    glad_glUniform3f = (PFNGLUNIFORM3FPROC) glad_gl_on_demand_loader("glUniform3f");
    glad_glUniform3f(location, v0, v1, v2);
}
PFNGLUNIFORM3FPROC glad_glUniform3f = glad_on_demand_impl_glUniform3f;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    glad_glUniform3fARB = (PFNGLUNIFORM3FARBPROC) glad_gl_on_demand_loader("glUniform3fARB");
    glad_glUniform3fARB(location, v0, v1, v2);
}
PFNGLUNIFORM3FARBPROC glad_glUniform3fARB = glad_on_demand_impl_glUniform3fARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3fv(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform3fv = (PFNGLUNIFORM3FVPROC) glad_gl_on_demand_loader("glUniform3fv");
    glad_glUniform3fv(location, count, value);
}
PFNGLUNIFORM3FVPROC glad_glUniform3fv = glad_on_demand_impl_glUniform3fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3fvARB(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform3fvARB = (PFNGLUNIFORM3FVARBPROC) glad_gl_on_demand_loader("glUniform3fvARB");
    glad_glUniform3fvARB(location, count, value);
}
PFNGLUNIFORM3FVARBPROC glad_glUniform3fvARB = glad_on_demand_impl_glUniform3fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
    glad_glUniform3i = (PFNGLUNIFORM3IPROC) glad_gl_on_demand_loader("glUniform3i");
    glad_glUniform3i(location, v0, v1, v2);
}
PFNGLUNIFORM3IPROC glad_glUniform3i = glad_on_demand_impl_glUniform3i;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3iARB(GLint location, GLint v0, GLint v1, GLint v2) {
    glad_glUniform3iARB = (PFNGLUNIFORM3IARBPROC) glad_gl_on_demand_loader("glUniform3iARB");
    glad_glUniform3iARB(location, v0, v1, v2);
}
PFNGLUNIFORM3IARBPROC glad_glUniform3iARB = glad_on_demand_impl_glUniform3iARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3iv(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform3iv = (PFNGLUNIFORM3IVPROC) glad_gl_on_demand_loader("glUniform3iv");
    glad_glUniform3iv(location, count, value);
}
PFNGLUNIFORM3IVPROC glad_glUniform3iv = glad_on_demand_impl_glUniform3iv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3ivARB(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform3ivARB = (PFNGLUNIFORM3IVARBPROC) glad_gl_on_demand_loader("glUniform3ivARB");
    glad_glUniform3ivARB(location, count, value);
}
PFNGLUNIFORM3IVARBPROC glad_glUniform3ivARB = glad_on_demand_impl_glUniform3ivARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) {
    glad_glUniform3ui = (PFNGLUNIFORM3UIPROC) glad_gl_on_demand_loader("glUniform3ui");
    glad_glUniform3ui(location, v0, v1, v2);
}
PFNGLUNIFORM3UIPROC glad_glUniform3ui = glad_on_demand_impl_glUniform3ui;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2) {
    glad_glUniform3uiEXT = (PFNGLUNIFORM3UIEXTPROC) glad_gl_on_demand_loader("glUniform3uiEXT");
    glad_glUniform3uiEXT(location, v0, v1, v2);
}
PFNGLUNIFORM3UIEXTPROC glad_glUniform3uiEXT = glad_on_demand_impl_glUniform3uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3uiv(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform3uiv = (PFNGLUNIFORM3UIVPROC) glad_gl_on_demand_loader("glUniform3uiv");
    glad_glUniform3uiv(location, count, value);
}
PFNGLUNIFORM3UIVPROC glad_glUniform3uiv = glad_on_demand_impl_glUniform3uiv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform3uivEXT(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform3uivEXT = (PFNGLUNIFORM3UIVEXTPROC) glad_gl_on_demand_loader("glUniform3uivEXT");
    glad_glUniform3uivEXT(location, count, value);
}
PFNGLUNIFORM3UIVEXTPROC glad_glUniform3uivEXT = glad_on_demand_impl_glUniform3uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glad_glUniform4f = (PFNGLUNIFORM4FPROC) glad_gl_on_demand_loader("glUniform4f");
    glad_glUniform4f(location, v0, v1, v2, v3);
}
PFNGLUNIFORM4FPROC glad_glUniform4f = glad_on_demand_impl_glUniform4f;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glad_glUniform4fARB = (PFNGLUNIFORM4FARBPROC) glad_gl_on_demand_loader("glUniform4fARB");
    glad_glUniform4fARB(location, v0, v1, v2, v3);
}
PFNGLUNIFORM4FARBPROC glad_glUniform4fARB = glad_on_demand_impl_glUniform4fARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4fv(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform4fv = (PFNGLUNIFORM4FVPROC) glad_gl_on_demand_loader("glUniform4fv");
    glad_glUniform4fv(location, count, value);
}
PFNGLUNIFORM4FVPROC glad_glUniform4fv = glad_on_demand_impl_glUniform4fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4fvARB(GLint location, GLsizei count, const GLfloat * value) {
    glad_glUniform4fvARB = (PFNGLUNIFORM4FVARBPROC) glad_gl_on_demand_loader("glUniform4fvARB");
    glad_glUniform4fvARB(location, count, value);
}
PFNGLUNIFORM4FVARBPROC glad_glUniform4fvARB = glad_on_demand_impl_glUniform4fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    glad_glUniform4i = (PFNGLUNIFORM4IPROC) glad_gl_on_demand_loader("glUniform4i");
    glad_glUniform4i(location, v0, v1, v2, v3);
}
PFNGLUNIFORM4IPROC glad_glUniform4i = glad_on_demand_impl_glUniform4i;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4iARB(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    glad_glUniform4iARB = (PFNGLUNIFORM4IARBPROC) glad_gl_on_demand_loader("glUniform4iARB");
    glad_glUniform4iARB(location, v0, v1, v2, v3);
}
PFNGLUNIFORM4IARBPROC glad_glUniform4iARB = glad_on_demand_impl_glUniform4iARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4iv(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform4iv = (PFNGLUNIFORM4IVPROC) glad_gl_on_demand_loader("glUniform4iv");
    glad_glUniform4iv(location, count, value);
}
PFNGLUNIFORM4IVPROC glad_glUniform4iv = glad_on_demand_impl_glUniform4iv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4ivARB(GLint location, GLsizei count, const GLint * value) {
    glad_glUniform4ivARB = (PFNGLUNIFORM4IVARBPROC) glad_gl_on_demand_loader("glUniform4ivARB");
    glad_glUniform4ivARB(location, count, value);
}
PFNGLUNIFORM4IVARBPROC glad_glUniform4ivARB = glad_on_demand_impl_glUniform4ivARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    glad_glUniform4ui = (PFNGLUNIFORM4UIPROC) glad_gl_on_demand_loader("glUniform4ui");
    glad_glUniform4ui(location, v0, v1, v2, v3);
}
PFNGLUNIFORM4UIPROC glad_glUniform4ui = glad_on_demand_impl_glUniform4ui;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    glad_glUniform4uiEXT = (PFNGLUNIFORM4UIEXTPROC) glad_gl_on_demand_loader("glUniform4uiEXT");
    glad_glUniform4uiEXT(location, v0, v1, v2, v3);
}
PFNGLUNIFORM4UIEXTPROC glad_glUniform4uiEXT = glad_on_demand_impl_glUniform4uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4uiv(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform4uiv = (PFNGLUNIFORM4UIVPROC) glad_gl_on_demand_loader("glUniform4uiv");
    glad_glUniform4uiv(location, count, value);
}
PFNGLUNIFORM4UIVPROC glad_glUniform4uiv = glad_on_demand_impl_glUniform4uiv;
static void GLAD_API_PTR glad_on_demand_impl_glUniform4uivEXT(GLint location, GLsizei count, const GLuint * value) {
    glad_glUniform4uivEXT = (PFNGLUNIFORM4UIVEXTPROC) glad_gl_on_demand_loader("glUniform4uivEXT");
    glad_glUniform4uivEXT(location, count, value);
}
PFNGLUNIFORM4UIVEXTPROC glad_glUniform4uivEXT = glad_on_demand_impl_glUniform4uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {
    glad_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC) glad_gl_on_demand_loader("glUniformBlockBinding");
    glad_glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}
PFNGLUNIFORMBLOCKBINDINGPROC glad_glUniformBlockBinding = glad_on_demand_impl_glUniformBlockBinding;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) glad_gl_on_demand_loader("glUniformMatrix2fv");
    glad_glUniformMatrix2fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv = glad_on_demand_impl_glUniformMatrix2fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix2fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC) glad_gl_on_demand_loader("glUniformMatrix2fvARB");
    glad_glUniformMatrix2fvARB(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX2FVARBPROC glad_glUniformMatrix2fvARB = glad_on_demand_impl_glUniformMatrix2fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) glad_gl_on_demand_loader("glUniformMatrix2x3fv");
    glad_glUniformMatrix2x3fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX2X3FVPROC glad_glUniformMatrix2x3fv = glad_on_demand_impl_glUniformMatrix2x3fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) glad_gl_on_demand_loader("glUniformMatrix2x4fv");
    glad_glUniformMatrix2x4fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX2X4FVPROC glad_glUniformMatrix2x4fv = glad_on_demand_impl_glUniformMatrix2x4fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) glad_gl_on_demand_loader("glUniformMatrix3fv");
    glad_glUniformMatrix3fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv = glad_on_demand_impl_glUniformMatrix3fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix3fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC) glad_gl_on_demand_loader("glUniformMatrix3fvARB");
    glad_glUniformMatrix3fvARB(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX3FVARBPROC glad_glUniformMatrix3fvARB = glad_on_demand_impl_glUniformMatrix3fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) glad_gl_on_demand_loader("glUniformMatrix3x2fv");
    glad_glUniformMatrix3x2fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX3X2FVPROC glad_glUniformMatrix3x2fv = glad_on_demand_impl_glUniformMatrix3x2fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) glad_gl_on_demand_loader("glUniformMatrix3x4fv");
    glad_glUniformMatrix3x4fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX3X4FVPROC glad_glUniformMatrix3x4fv = glad_on_demand_impl_glUniformMatrix3x4fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) glad_gl_on_demand_loader("glUniformMatrix4fv");
    glad_glUniformMatrix4fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = glad_on_demand_impl_glUniformMatrix4fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix4fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC) glad_gl_on_demand_loader("glUniformMatrix4fvARB");
    glad_glUniformMatrix4fvARB(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX4FVARBPROC glad_glUniformMatrix4fvARB = glad_on_demand_impl_glUniformMatrix4fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) glad_gl_on_demand_loader("glUniformMatrix4x2fv");
    glad_glUniformMatrix4x2fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX4X2FVPROC glad_glUniformMatrix4x2fv = glad_on_demand_impl_glUniformMatrix4x2fv;
static void GLAD_API_PTR glad_on_demand_impl_glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glad_glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) glad_gl_on_demand_loader("glUniformMatrix4x3fv");
    glad_glUniformMatrix4x3fv(location, count, transpose, value);
}
PFNGLUNIFORMMATRIX4X3FVPROC glad_glUniformMatrix4x3fv = glad_on_demand_impl_glUniformMatrix4x3fv;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glUnmapBuffer(GLenum target) {
    glad_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) glad_gl_on_demand_loader("glUnmapBuffer");
    return glad_glUnmapBuffer(target);
}
PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer = glad_on_demand_impl_glUnmapBuffer;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glUnmapBufferARB(GLenum target) {
    glad_glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) glad_gl_on_demand_loader("glUnmapBufferARB");
    return glad_glUnmapBufferARB(target);
}
PFNGLUNMAPBUFFERARBPROC glad_glUnmapBufferARB = glad_on_demand_impl_glUnmapBufferARB;
static GLboolean GLAD_API_PTR glad_on_demand_impl_glUnmapNamedBufferEXT(GLuint buffer) {
    glad_glUnmapNamedBufferEXT = (PFNGLUNMAPNAMEDBUFFEREXTPROC) glad_gl_on_demand_loader("glUnmapNamedBufferEXT");
    return glad_glUnmapNamedBufferEXT(buffer);
}
PFNGLUNMAPNAMEDBUFFEREXTPROC glad_glUnmapNamedBufferEXT = glad_on_demand_impl_glUnmapNamedBufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glUseProgram(GLuint program) {
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC) glad_gl_on_demand_loader("glUseProgram");
    glad_glUseProgram(program);
}
PFNGLUSEPROGRAMPROC glad_glUseProgram = glad_on_demand_impl_glUseProgram;
static void GLAD_API_PTR glad_on_demand_impl_glUseProgramObjectARB(GLhandleARB programObj) {
    glad_glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) glad_gl_on_demand_loader("glUseProgramObjectARB");
    glad_glUseProgramObjectARB(programObj);
}
PFNGLUSEPROGRAMOBJECTARBPROC glad_glUseProgramObjectARB = glad_on_demand_impl_glUseProgramObjectARB;
static void GLAD_API_PTR glad_on_demand_impl_glValidateProgram(GLuint program) {
    glad_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) glad_gl_on_demand_loader("glValidateProgram");
    glad_glValidateProgram(program);
}
PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram = glad_on_demand_impl_glValidateProgram;
static void GLAD_API_PTR glad_on_demand_impl_glValidateProgramARB(GLhandleARB programObj) {
    glad_glValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC) glad_gl_on_demand_loader("glValidateProgramARB");
    glad_glValidateProgramARB(programObj);
}
PFNGLVALIDATEPROGRAMARBPROC glad_glValidateProgramARB = glad_on_demand_impl_glValidateProgramARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayBindVertexBufferEXT(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) {
    glad_glVertexArrayBindVertexBufferEXT = (PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC) glad_gl_on_demand_loader("glVertexArrayBindVertexBufferEXT");
    glad_glVertexArrayBindVertexBufferEXT(vaobj, bindingindex, buffer, offset, stride);
}
PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC glad_glVertexArrayBindVertexBufferEXT = glad_on_demand_impl_glVertexArrayBindVertexBufferEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayColorOffsetEXT = (PFNGLVERTEXARRAYCOLOROFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayColorOffsetEXT");
    glad_glVertexArrayColorOffsetEXT(vaobj, buffer, size, type, stride, offset);
}
PFNGLVERTEXARRAYCOLOROFFSETEXTPROC glad_glVertexArrayColorOffsetEXT = glad_on_demand_impl_glVertexArrayColorOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayEdgeFlagOffsetEXT(GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayEdgeFlagOffsetEXT = (PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayEdgeFlagOffsetEXT");
    glad_glVertexArrayEdgeFlagOffsetEXT(vaobj, buffer, stride, offset);
}
PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC glad_glVertexArrayEdgeFlagOffsetEXT = glad_on_demand_impl_glVertexArrayEdgeFlagOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayFogCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayFogCoordOffsetEXT = (PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayFogCoordOffsetEXT");
    glad_glVertexArrayFogCoordOffsetEXT(vaobj, buffer, type, stride, offset);
}
PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC glad_glVertexArrayFogCoordOffsetEXT = glad_on_demand_impl_glVertexArrayFogCoordOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayIndexOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayIndexOffsetEXT = (PFNGLVERTEXARRAYINDEXOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayIndexOffsetEXT");
    glad_glVertexArrayIndexOffsetEXT(vaobj, buffer, type, stride, offset);
}
PFNGLVERTEXARRAYINDEXOFFSETEXTPROC glad_glVertexArrayIndexOffsetEXT = glad_on_demand_impl_glVertexArrayIndexOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayMultiTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayMultiTexCoordOffsetEXT = (PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayMultiTexCoordOffsetEXT");
    glad_glVertexArrayMultiTexCoordOffsetEXT(vaobj, buffer, texunit, size, type, stride, offset);
}
PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC glad_glVertexArrayMultiTexCoordOffsetEXT = glad_on_demand_impl_glVertexArrayMultiTexCoordOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayNormalOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayNormalOffsetEXT = (PFNGLVERTEXARRAYNORMALOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayNormalOffsetEXT");
    glad_glVertexArrayNormalOffsetEXT(vaobj, buffer, type, stride, offset);
}
PFNGLVERTEXARRAYNORMALOFFSETEXTPROC glad_glVertexArrayNormalOffsetEXT = glad_on_demand_impl_glVertexArrayNormalOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArraySecondaryColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArraySecondaryColorOffsetEXT = (PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArraySecondaryColorOffsetEXT");
    glad_glVertexArraySecondaryColorOffsetEXT(vaobj, buffer, size, type, stride, offset);
}
PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC glad_glVertexArraySecondaryColorOffsetEXT = glad_on_demand_impl_glVertexArraySecondaryColorOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayTexCoordOffsetEXT = (PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayTexCoordOffsetEXT");
    glad_glVertexArrayTexCoordOffsetEXT(vaobj, buffer, size, type, stride, offset);
}
PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC glad_glVertexArrayTexCoordOffsetEXT = glad_on_demand_impl_glVertexArrayTexCoordOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexAttribBindingEXT(GLuint vaobj, GLuint attribindex, GLuint bindingindex) {
    glad_glVertexArrayVertexAttribBindingEXT = (PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexAttribBindingEXT");
    glad_glVertexArrayVertexAttribBindingEXT(vaobj, attribindex, bindingindex);
}
PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC glad_glVertexArrayVertexAttribBindingEXT = glad_on_demand_impl_glVertexArrayVertexAttribBindingEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexAttribDivisorEXT(GLuint vaobj, GLuint index, GLuint divisor) {
    glad_glVertexArrayVertexAttribDivisorEXT = (PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexAttribDivisorEXT");
    glad_glVertexArrayVertexAttribDivisorEXT(vaobj, index, divisor);
}
PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC glad_glVertexArrayVertexAttribDivisorEXT = glad_on_demand_impl_glVertexArrayVertexAttribDivisorEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexAttribFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) {
    glad_glVertexArrayVertexAttribFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexAttribFormatEXT");
    glad_glVertexArrayVertexAttribFormatEXT(vaobj, attribindex, size, type, normalized, relativeoffset);
}
PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC glad_glVertexArrayVertexAttribFormatEXT = glad_on_demand_impl_glVertexArrayVertexAttribFormatEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexAttribIFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
    glad_glVertexArrayVertexAttribIFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexAttribIFormatEXT");
    glad_glVertexArrayVertexAttribIFormatEXT(vaobj, attribindex, size, type, relativeoffset);
}
PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC glad_glVertexArrayVertexAttribIFormatEXT = glad_on_demand_impl_glVertexArrayVertexAttribIFormatEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexAttribIOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayVertexAttribIOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexAttribIOffsetEXT");
    glad_glVertexArrayVertexAttribIOffsetEXT(vaobj, buffer, index, size, type, stride, offset);
}
PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC glad_glVertexArrayVertexAttribIOffsetEXT = glad_on_demand_impl_glVertexArrayVertexAttribIOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexAttribLFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
    glad_glVertexArrayVertexAttribLFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexAttribLFormatEXT");
    glad_glVertexArrayVertexAttribLFormatEXT(vaobj, attribindex, size, type, relativeoffset);
}
PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC glad_glVertexArrayVertexAttribLFormatEXT = glad_on_demand_impl_glVertexArrayVertexAttribLFormatEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexAttribLOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayVertexAttribLOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexAttribLOffsetEXT");
    glad_glVertexArrayVertexAttribLOffsetEXT(vaobj, buffer, index, size, type, stride, offset);
}
PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC glad_glVertexArrayVertexAttribLOffsetEXT = glad_on_demand_impl_glVertexArrayVertexAttribLOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexAttribOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayVertexAttribOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexAttribOffsetEXT");
    glad_glVertexArrayVertexAttribOffsetEXT(vaobj, buffer, index, size, type, normalized, stride, offset);
}
PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC glad_glVertexArrayVertexAttribOffsetEXT = glad_on_demand_impl_glVertexArrayVertexAttribOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexBindingDivisorEXT(GLuint vaobj, GLuint bindingindex, GLuint divisor) {
    glad_glVertexArrayVertexBindingDivisorEXT = (PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexBindingDivisorEXT");
    glad_glVertexArrayVertexBindingDivisorEXT(vaobj, bindingindex, divisor);
}
PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC glad_glVertexArrayVertexBindingDivisorEXT = glad_on_demand_impl_glVertexArrayVertexBindingDivisorEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexArrayVertexOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) {
    glad_glVertexArrayVertexOffsetEXT = (PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC) glad_gl_on_demand_loader("glVertexArrayVertexOffsetEXT");
    glad_glVertexArrayVertexOffsetEXT(vaobj, buffer, size, type, stride, offset);
}
PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC glad_glVertexArrayVertexOffsetEXT = glad_on_demand_impl_glVertexArrayVertexOffsetEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1d(GLuint index, GLdouble x) {
    glad_glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC) glad_gl_on_demand_loader("glVertexAttrib1d");
    glad_glVertexAttrib1d(index, x);
}
PFNGLVERTEXATTRIB1DPROC glad_glVertexAttrib1d = glad_on_demand_impl_glVertexAttrib1d;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1dARB(GLuint index, GLdouble x) {
    glad_glVertexAttrib1dARB = (PFNGLVERTEXATTRIB1DARBPROC) glad_gl_on_demand_loader("glVertexAttrib1dARB");
    glad_glVertexAttrib1dARB(index, x);
}
PFNGLVERTEXATTRIB1DARBPROC glad_glVertexAttrib1dARB = glad_on_demand_impl_glVertexAttrib1dARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1dNV(GLuint index, GLdouble x) {
    glad_glVertexAttrib1dNV = (PFNGLVERTEXATTRIB1DNVPROC) glad_gl_on_demand_loader("glVertexAttrib1dNV");
    glad_glVertexAttrib1dNV(index, x);
}
PFNGLVERTEXATTRIB1DNVPROC glad_glVertexAttrib1dNV = glad_on_demand_impl_glVertexAttrib1dNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1dv(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC) glad_gl_on_demand_loader("glVertexAttrib1dv");
    glad_glVertexAttrib1dv(index, v);
}
PFNGLVERTEXATTRIB1DVPROC glad_glVertexAttrib1dv = glad_on_demand_impl_glVertexAttrib1dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1dvARB(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib1dvARB = (PFNGLVERTEXATTRIB1DVARBPROC) glad_gl_on_demand_loader("glVertexAttrib1dvARB");
    glad_glVertexAttrib1dvARB(index, v);
}
PFNGLVERTEXATTRIB1DVARBPROC glad_glVertexAttrib1dvARB = glad_on_demand_impl_glVertexAttrib1dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1dvNV(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib1dvNV = (PFNGLVERTEXATTRIB1DVNVPROC) glad_gl_on_demand_loader("glVertexAttrib1dvNV");
    glad_glVertexAttrib1dvNV(index, v);
}
PFNGLVERTEXATTRIB1DVNVPROC glad_glVertexAttrib1dvNV = glad_on_demand_impl_glVertexAttrib1dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1f(GLuint index, GLfloat x) {
    glad_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC) glad_gl_on_demand_loader("glVertexAttrib1f");
    glad_glVertexAttrib1f(index, x);
}
PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f = glad_on_demand_impl_glVertexAttrib1f;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1fARB(GLuint index, GLfloat x) {
    glad_glVertexAttrib1fARB = (PFNGLVERTEXATTRIB1FARBPROC) glad_gl_on_demand_loader("glVertexAttrib1fARB");
    glad_glVertexAttrib1fARB(index, x);
}
PFNGLVERTEXATTRIB1FARBPROC glad_glVertexAttrib1fARB = glad_on_demand_impl_glVertexAttrib1fARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1fNV(GLuint index, GLfloat x) {
    glad_glVertexAttrib1fNV = (PFNGLVERTEXATTRIB1FNVPROC) glad_gl_on_demand_loader("glVertexAttrib1fNV");
    glad_glVertexAttrib1fNV(index, x);
}
PFNGLVERTEXATTRIB1FNVPROC glad_glVertexAttrib1fNV = glad_on_demand_impl_glVertexAttrib1fNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1fv(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC) glad_gl_on_demand_loader("glVertexAttrib1fv");
    glad_glVertexAttrib1fv(index, v);
}
PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv = glad_on_demand_impl_glVertexAttrib1fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1fvARB(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib1fvARB = (PFNGLVERTEXATTRIB1FVARBPROC) glad_gl_on_demand_loader("glVertexAttrib1fvARB");
    glad_glVertexAttrib1fvARB(index, v);
}
PFNGLVERTEXATTRIB1FVARBPROC glad_glVertexAttrib1fvARB = glad_on_demand_impl_glVertexAttrib1fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1fvNV(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib1fvNV = (PFNGLVERTEXATTRIB1FVNVPROC) glad_gl_on_demand_loader("glVertexAttrib1fvNV");
    glad_glVertexAttrib1fvNV(index, v);
}
PFNGLVERTEXATTRIB1FVNVPROC glad_glVertexAttrib1fvNV = glad_on_demand_impl_glVertexAttrib1fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1s(GLuint index, GLshort x) {
    glad_glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC) glad_gl_on_demand_loader("glVertexAttrib1s");
    glad_glVertexAttrib1s(index, x);
}
PFNGLVERTEXATTRIB1SPROC glad_glVertexAttrib1s = glad_on_demand_impl_glVertexAttrib1s;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1sARB(GLuint index, GLshort x) {
    glad_glVertexAttrib1sARB = (PFNGLVERTEXATTRIB1SARBPROC) glad_gl_on_demand_loader("glVertexAttrib1sARB");
    glad_glVertexAttrib1sARB(index, x);
}
PFNGLVERTEXATTRIB1SARBPROC glad_glVertexAttrib1sARB = glad_on_demand_impl_glVertexAttrib1sARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1sNV(GLuint index, GLshort x) {
    glad_glVertexAttrib1sNV = (PFNGLVERTEXATTRIB1SNVPROC) glad_gl_on_demand_loader("glVertexAttrib1sNV");
    glad_glVertexAttrib1sNV(index, x);
}
PFNGLVERTEXATTRIB1SNVPROC glad_glVertexAttrib1sNV = glad_on_demand_impl_glVertexAttrib1sNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1sv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC) glad_gl_on_demand_loader("glVertexAttrib1sv");
    glad_glVertexAttrib1sv(index, v);
}
PFNGLVERTEXATTRIB1SVPROC glad_glVertexAttrib1sv = glad_on_demand_impl_glVertexAttrib1sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1svARB(GLuint index, const GLshort * v) {
    glad_glVertexAttrib1svARB = (PFNGLVERTEXATTRIB1SVARBPROC) glad_gl_on_demand_loader("glVertexAttrib1svARB");
    glad_glVertexAttrib1svARB(index, v);
}
PFNGLVERTEXATTRIB1SVARBPROC glad_glVertexAttrib1svARB = glad_on_demand_impl_glVertexAttrib1svARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib1svNV(GLuint index, const GLshort * v) {
    glad_glVertexAttrib1svNV = (PFNGLVERTEXATTRIB1SVNVPROC) glad_gl_on_demand_loader("glVertexAttrib1svNV");
    glad_glVertexAttrib1svNV(index, v);
}
PFNGLVERTEXATTRIB1SVNVPROC glad_glVertexAttrib1svNV = glad_on_demand_impl_glVertexAttrib1svNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y) {
    glad_glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC) glad_gl_on_demand_loader("glVertexAttrib2d");
    glad_glVertexAttrib2d(index, x, y);
}
PFNGLVERTEXATTRIB2DPROC glad_glVertexAttrib2d = glad_on_demand_impl_glVertexAttrib2d;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2dARB(GLuint index, GLdouble x, GLdouble y) {
    glad_glVertexAttrib2dARB = (PFNGLVERTEXATTRIB2DARBPROC) glad_gl_on_demand_loader("glVertexAttrib2dARB");
    glad_glVertexAttrib2dARB(index, x, y);
}
PFNGLVERTEXATTRIB2DARBPROC glad_glVertexAttrib2dARB = glad_on_demand_impl_glVertexAttrib2dARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2dNV(GLuint index, GLdouble x, GLdouble y) {
    glad_glVertexAttrib2dNV = (PFNGLVERTEXATTRIB2DNVPROC) glad_gl_on_demand_loader("glVertexAttrib2dNV");
    glad_glVertexAttrib2dNV(index, x, y);
}
PFNGLVERTEXATTRIB2DNVPROC glad_glVertexAttrib2dNV = glad_on_demand_impl_glVertexAttrib2dNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2dv(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC) glad_gl_on_demand_loader("glVertexAttrib2dv");
    glad_glVertexAttrib2dv(index, v);
}
PFNGLVERTEXATTRIB2DVPROC glad_glVertexAttrib2dv = glad_on_demand_impl_glVertexAttrib2dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2dvARB(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib2dvARB = (PFNGLVERTEXATTRIB2DVARBPROC) glad_gl_on_demand_loader("glVertexAttrib2dvARB");
    glad_glVertexAttrib2dvARB(index, v);
}
PFNGLVERTEXATTRIB2DVARBPROC glad_glVertexAttrib2dvARB = glad_on_demand_impl_glVertexAttrib2dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2dvNV(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib2dvNV = (PFNGLVERTEXATTRIB2DVNVPROC) glad_gl_on_demand_loader("glVertexAttrib2dvNV");
    glad_glVertexAttrib2dvNV(index, v);
}
PFNGLVERTEXATTRIB2DVNVPROC glad_glVertexAttrib2dvNV = glad_on_demand_impl_glVertexAttrib2dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
    glad_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC) glad_gl_on_demand_loader("glVertexAttrib2f");
    glad_glVertexAttrib2f(index, x, y);
}
PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f = glad_on_demand_impl_glVertexAttrib2f;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2fARB(GLuint index, GLfloat x, GLfloat y) {
    glad_glVertexAttrib2fARB = (PFNGLVERTEXATTRIB2FARBPROC) glad_gl_on_demand_loader("glVertexAttrib2fARB");
    glad_glVertexAttrib2fARB(index, x, y);
}
PFNGLVERTEXATTRIB2FARBPROC glad_glVertexAttrib2fARB = glad_on_demand_impl_glVertexAttrib2fARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2fNV(GLuint index, GLfloat x, GLfloat y) {
    glad_glVertexAttrib2fNV = (PFNGLVERTEXATTRIB2FNVPROC) glad_gl_on_demand_loader("glVertexAttrib2fNV");
    glad_glVertexAttrib2fNV(index, x, y);
}
PFNGLVERTEXATTRIB2FNVPROC glad_glVertexAttrib2fNV = glad_on_demand_impl_glVertexAttrib2fNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2fv(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC) glad_gl_on_demand_loader("glVertexAttrib2fv");
    glad_glVertexAttrib2fv(index, v);
}
PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv = glad_on_demand_impl_glVertexAttrib2fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2fvARB(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib2fvARB = (PFNGLVERTEXATTRIB2FVARBPROC) glad_gl_on_demand_loader("glVertexAttrib2fvARB");
    glad_glVertexAttrib2fvARB(index, v);
}
PFNGLVERTEXATTRIB2FVARBPROC glad_glVertexAttrib2fvARB = glad_on_demand_impl_glVertexAttrib2fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2fvNV(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib2fvNV = (PFNGLVERTEXATTRIB2FVNVPROC) glad_gl_on_demand_loader("glVertexAttrib2fvNV");
    glad_glVertexAttrib2fvNV(index, v);
}
PFNGLVERTEXATTRIB2FVNVPROC glad_glVertexAttrib2fvNV = glad_on_demand_impl_glVertexAttrib2fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2s(GLuint index, GLshort x, GLshort y) {
    glad_glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC) glad_gl_on_demand_loader("glVertexAttrib2s");
    glad_glVertexAttrib2s(index, x, y);
}
PFNGLVERTEXATTRIB2SPROC glad_glVertexAttrib2s = glad_on_demand_impl_glVertexAttrib2s;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2sARB(GLuint index, GLshort x, GLshort y) {
    glad_glVertexAttrib2sARB = (PFNGLVERTEXATTRIB2SARBPROC) glad_gl_on_demand_loader("glVertexAttrib2sARB");
    glad_glVertexAttrib2sARB(index, x, y);
}
PFNGLVERTEXATTRIB2SARBPROC glad_glVertexAttrib2sARB = glad_on_demand_impl_glVertexAttrib2sARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2sNV(GLuint index, GLshort x, GLshort y) {
    glad_glVertexAttrib2sNV = (PFNGLVERTEXATTRIB2SNVPROC) glad_gl_on_demand_loader("glVertexAttrib2sNV");
    glad_glVertexAttrib2sNV(index, x, y);
}
PFNGLVERTEXATTRIB2SNVPROC glad_glVertexAttrib2sNV = glad_on_demand_impl_glVertexAttrib2sNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2sv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC) glad_gl_on_demand_loader("glVertexAttrib2sv");
    glad_glVertexAttrib2sv(index, v);
}
PFNGLVERTEXATTRIB2SVPROC glad_glVertexAttrib2sv = glad_on_demand_impl_glVertexAttrib2sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2svARB(GLuint index, const GLshort * v) {
    glad_glVertexAttrib2svARB = (PFNGLVERTEXATTRIB2SVARBPROC) glad_gl_on_demand_loader("glVertexAttrib2svARB");
    glad_glVertexAttrib2svARB(index, v);
}
PFNGLVERTEXATTRIB2SVARBPROC glad_glVertexAttrib2svARB = glad_on_demand_impl_glVertexAttrib2svARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib2svNV(GLuint index, const GLshort * v) {
    glad_glVertexAttrib2svNV = (PFNGLVERTEXATTRIB2SVNVPROC) glad_gl_on_demand_loader("glVertexAttrib2svNV");
    glad_glVertexAttrib2svNV(index, v);
}
PFNGLVERTEXATTRIB2SVNVPROC glad_glVertexAttrib2svNV = glad_on_demand_impl_glVertexAttrib2svNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) {
    glad_glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC) glad_gl_on_demand_loader("glVertexAttrib3d");
    glad_glVertexAttrib3d(index, x, y, z);
}
PFNGLVERTEXATTRIB3DPROC glad_glVertexAttrib3d = glad_on_demand_impl_glVertexAttrib3d;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z) {
    glad_glVertexAttrib3dARB = (PFNGLVERTEXATTRIB3DARBPROC) glad_gl_on_demand_loader("glVertexAttrib3dARB");
    glad_glVertexAttrib3dARB(index, x, y, z);
}
PFNGLVERTEXATTRIB3DARBPROC glad_glVertexAttrib3dARB = glad_on_demand_impl_glVertexAttrib3dARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z) {
    glad_glVertexAttrib3dNV = (PFNGLVERTEXATTRIB3DNVPROC) glad_gl_on_demand_loader("glVertexAttrib3dNV");
    glad_glVertexAttrib3dNV(index, x, y, z);
}
PFNGLVERTEXATTRIB3DNVPROC glad_glVertexAttrib3dNV = glad_on_demand_impl_glVertexAttrib3dNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3dv(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC) glad_gl_on_demand_loader("glVertexAttrib3dv");
    glad_glVertexAttrib3dv(index, v);
}
PFNGLVERTEXATTRIB3DVPROC glad_glVertexAttrib3dv = glad_on_demand_impl_glVertexAttrib3dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3dvARB(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib3dvARB = (PFNGLVERTEXATTRIB3DVARBPROC) glad_gl_on_demand_loader("glVertexAttrib3dvARB");
    glad_glVertexAttrib3dvARB(index, v);
}
PFNGLVERTEXATTRIB3DVARBPROC glad_glVertexAttrib3dvARB = glad_on_demand_impl_glVertexAttrib3dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3dvNV(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib3dvNV = (PFNGLVERTEXATTRIB3DVNVPROC) glad_gl_on_demand_loader("glVertexAttrib3dvNV");
    glad_glVertexAttrib3dvNV(index, v);
}
PFNGLVERTEXATTRIB3DVNVPROC glad_glVertexAttrib3dvNV = glad_on_demand_impl_glVertexAttrib3dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    glad_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC) glad_gl_on_demand_loader("glVertexAttrib3f");
    glad_glVertexAttrib3f(index, x, y, z);
}
PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f = glad_on_demand_impl_glVertexAttrib3f;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    glad_glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC) glad_gl_on_demand_loader("glVertexAttrib3fARB");
    glad_glVertexAttrib3fARB(index, x, y, z);
}
PFNGLVERTEXATTRIB3FARBPROC glad_glVertexAttrib3fARB = glad_on_demand_impl_glVertexAttrib3fARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    glad_glVertexAttrib3fNV = (PFNGLVERTEXATTRIB3FNVPROC) glad_gl_on_demand_loader("glVertexAttrib3fNV");
    glad_glVertexAttrib3fNV(index, x, y, z);
}
PFNGLVERTEXATTRIB3FNVPROC glad_glVertexAttrib3fNV = glad_on_demand_impl_glVertexAttrib3fNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3fv(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC) glad_gl_on_demand_loader("glVertexAttrib3fv");
    glad_glVertexAttrib3fv(index, v);
}
PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv = glad_on_demand_impl_glVertexAttrib3fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3fvARB(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib3fvARB = (PFNGLVERTEXATTRIB3FVARBPROC) glad_gl_on_demand_loader("glVertexAttrib3fvARB");
    glad_glVertexAttrib3fvARB(index, v);
}
PFNGLVERTEXATTRIB3FVARBPROC glad_glVertexAttrib3fvARB = glad_on_demand_impl_glVertexAttrib3fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3fvNV(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib3fvNV = (PFNGLVERTEXATTRIB3FVNVPROC) glad_gl_on_demand_loader("glVertexAttrib3fvNV");
    glad_glVertexAttrib3fvNV(index, v);
}
PFNGLVERTEXATTRIB3FVNVPROC glad_glVertexAttrib3fvNV = glad_on_demand_impl_glVertexAttrib3fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) {
    glad_glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC) glad_gl_on_demand_loader("glVertexAttrib3s");
    glad_glVertexAttrib3s(index, x, y, z);
}
PFNGLVERTEXATTRIB3SPROC glad_glVertexAttrib3s = glad_on_demand_impl_glVertexAttrib3s;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3sARB(GLuint index, GLshort x, GLshort y, GLshort z) {
    glad_glVertexAttrib3sARB = (PFNGLVERTEXATTRIB3SARBPROC) glad_gl_on_demand_loader("glVertexAttrib3sARB");
    glad_glVertexAttrib3sARB(index, x, y, z);
}
PFNGLVERTEXATTRIB3SARBPROC glad_glVertexAttrib3sARB = glad_on_demand_impl_glVertexAttrib3sARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3sNV(GLuint index, GLshort x, GLshort y, GLshort z) {
    glad_glVertexAttrib3sNV = (PFNGLVERTEXATTRIB3SNVPROC) glad_gl_on_demand_loader("glVertexAttrib3sNV");
    glad_glVertexAttrib3sNV(index, x, y, z);
}
PFNGLVERTEXATTRIB3SNVPROC glad_glVertexAttrib3sNV = glad_on_demand_impl_glVertexAttrib3sNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3sv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC) glad_gl_on_demand_loader("glVertexAttrib3sv");
    glad_glVertexAttrib3sv(index, v);
}
PFNGLVERTEXATTRIB3SVPROC glad_glVertexAttrib3sv = glad_on_demand_impl_glVertexAttrib3sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3svARB(GLuint index, const GLshort * v) {
    glad_glVertexAttrib3svARB = (PFNGLVERTEXATTRIB3SVARBPROC) glad_gl_on_demand_loader("glVertexAttrib3svARB");
    glad_glVertexAttrib3svARB(index, v);
}
PFNGLVERTEXATTRIB3SVARBPROC glad_glVertexAttrib3svARB = glad_on_demand_impl_glVertexAttrib3svARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib3svNV(GLuint index, const GLshort * v) {
    glad_glVertexAttrib3svNV = (PFNGLVERTEXATTRIB3SVNVPROC) glad_gl_on_demand_loader("glVertexAttrib3svNV");
    glad_glVertexAttrib3svNV(index, v);
}
PFNGLVERTEXATTRIB3SVNVPROC glad_glVertexAttrib3svNV = glad_on_demand_impl_glVertexAttrib3svNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nbv(GLuint index, const GLbyte * v) {
    glad_glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nbv");
    glad_glVertexAttrib4Nbv(index, v);
}
PFNGLVERTEXATTRIB4NBVPROC glad_glVertexAttrib4Nbv = glad_on_demand_impl_glVertexAttrib4Nbv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4NbvARB(GLuint index, const GLbyte * v) {
    glad_glVertexAttrib4NbvARB = (PFNGLVERTEXATTRIB4NBVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4NbvARB");
    glad_glVertexAttrib4NbvARB(index, v);
}
PFNGLVERTEXATTRIB4NBVARBPROC glad_glVertexAttrib4NbvARB = glad_on_demand_impl_glVertexAttrib4NbvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Niv(GLuint index, const GLint * v) {
    glad_glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC) glad_gl_on_demand_loader("glVertexAttrib4Niv");
    glad_glVertexAttrib4Niv(index, v);
}
PFNGLVERTEXATTRIB4NIVPROC glad_glVertexAttrib4Niv = glad_on_demand_impl_glVertexAttrib4Niv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4NivARB(GLuint index, const GLint * v) {
    glad_glVertexAttrib4NivARB = (PFNGLVERTEXATTRIB4NIVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4NivARB");
    glad_glVertexAttrib4NivARB(index, v);
}
PFNGLVERTEXATTRIB4NIVARBPROC glad_glVertexAttrib4NivARB = glad_on_demand_impl_glVertexAttrib4NivARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nsv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nsv");
    glad_glVertexAttrib4Nsv(index, v);
}
PFNGLVERTEXATTRIB4NSVPROC glad_glVertexAttrib4Nsv = glad_on_demand_impl_glVertexAttrib4Nsv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4NsvARB(GLuint index, const GLshort * v) {
    glad_glVertexAttrib4NsvARB = (PFNGLVERTEXATTRIB4NSVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4NsvARB");
    glad_glVertexAttrib4NsvARB(index, v);
}
PFNGLVERTEXATTRIB4NSVARBPROC glad_glVertexAttrib4NsvARB = glad_on_demand_impl_glVertexAttrib4NsvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {
    glad_glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC) glad_gl_on_demand_loader("glVertexAttrib4Nub");
    glad_glVertexAttrib4Nub(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4NUBPROC glad_glVertexAttrib4Nub = glad_on_demand_impl_glVertexAttrib4Nub;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4NubARB(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {
    glad_glVertexAttrib4NubARB = (PFNGLVERTEXATTRIB4NUBARBPROC) glad_gl_on_demand_loader("glVertexAttrib4NubARB");
    glad_glVertexAttrib4NubARB(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4NUBARBPROC glad_glVertexAttrib4NubARB = glad_on_demand_impl_glVertexAttrib4NubARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nubv(GLuint index, const GLubyte * v) {
    glad_glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nubv");
    glad_glVertexAttrib4Nubv(index, v);
}
PFNGLVERTEXATTRIB4NUBVPROC glad_glVertexAttrib4Nubv = glad_on_demand_impl_glVertexAttrib4Nubv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4NubvARB(GLuint index, const GLubyte * v) {
    glad_glVertexAttrib4NubvARB = (PFNGLVERTEXATTRIB4NUBVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4NubvARB");
    glad_glVertexAttrib4NubvARB(index, v);
}
PFNGLVERTEXATTRIB4NUBVARBPROC glad_glVertexAttrib4NubvARB = glad_on_demand_impl_glVertexAttrib4NubvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nuiv(GLuint index, const GLuint * v) {
    glad_glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nuiv");
    glad_glVertexAttrib4Nuiv(index, v);
}
PFNGLVERTEXATTRIB4NUIVPROC glad_glVertexAttrib4Nuiv = glad_on_demand_impl_glVertexAttrib4Nuiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4NuivARB(GLuint index, const GLuint * v) {
    glad_glVertexAttrib4NuivARB = (PFNGLVERTEXATTRIB4NUIVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4NuivARB");
    glad_glVertexAttrib4NuivARB(index, v);
}
PFNGLVERTEXATTRIB4NUIVARBPROC glad_glVertexAttrib4NuivARB = glad_on_demand_impl_glVertexAttrib4NuivARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4Nusv(GLuint index, const GLushort * v) {
    glad_glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC) glad_gl_on_demand_loader("glVertexAttrib4Nusv");
    glad_glVertexAttrib4Nusv(index, v);
}
PFNGLVERTEXATTRIB4NUSVPROC glad_glVertexAttrib4Nusv = glad_on_demand_impl_glVertexAttrib4Nusv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4NusvARB(GLuint index, const GLushort * v) {
    glad_glVertexAttrib4NusvARB = (PFNGLVERTEXATTRIB4NUSVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4NusvARB");
    glad_glVertexAttrib4NusvARB(index, v);
}
PFNGLVERTEXATTRIB4NUSVARBPROC glad_glVertexAttrib4NusvARB = glad_on_demand_impl_glVertexAttrib4NusvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4bv(GLuint index, const GLbyte * v) {
    glad_glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC) glad_gl_on_demand_loader("glVertexAttrib4bv");
    glad_glVertexAttrib4bv(index, v);
}
PFNGLVERTEXATTRIB4BVPROC glad_glVertexAttrib4bv = glad_on_demand_impl_glVertexAttrib4bv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4bvARB(GLuint index, const GLbyte * v) {
    glad_glVertexAttrib4bvARB = (PFNGLVERTEXATTRIB4BVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4bvARB");
    glad_glVertexAttrib4bvARB(index, v);
}
PFNGLVERTEXATTRIB4BVARBPROC glad_glVertexAttrib4bvARB = glad_on_demand_impl_glVertexAttrib4bvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC) glad_gl_on_demand_loader("glVertexAttrib4d");
    glad_glVertexAttrib4d(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4DPROC glad_glVertexAttrib4d = glad_on_demand_impl_glVertexAttrib4d;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glVertexAttrib4dARB = (PFNGLVERTEXATTRIB4DARBPROC) glad_gl_on_demand_loader("glVertexAttrib4dARB");
    glad_glVertexAttrib4dARB(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4DARBPROC glad_glVertexAttrib4dARB = glad_on_demand_impl_glVertexAttrib4dARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    glad_glVertexAttrib4dNV = (PFNGLVERTEXATTRIB4DNVPROC) glad_gl_on_demand_loader("glVertexAttrib4dNV");
    glad_glVertexAttrib4dNV(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4DNVPROC glad_glVertexAttrib4dNV = glad_on_demand_impl_glVertexAttrib4dNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4dv(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC) glad_gl_on_demand_loader("glVertexAttrib4dv");
    glad_glVertexAttrib4dv(index, v);
}
PFNGLVERTEXATTRIB4DVPROC glad_glVertexAttrib4dv = glad_on_demand_impl_glVertexAttrib4dv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4dvARB(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib4dvARB = (PFNGLVERTEXATTRIB4DVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4dvARB");
    glad_glVertexAttrib4dvARB(index, v);
}
PFNGLVERTEXATTRIB4DVARBPROC glad_glVertexAttrib4dvARB = glad_on_demand_impl_glVertexAttrib4dvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4dvNV(GLuint index, const GLdouble * v) {
    glad_glVertexAttrib4dvNV = (PFNGLVERTEXATTRIB4DVNVPROC) glad_gl_on_demand_loader("glVertexAttrib4dvNV");
    glad_glVertexAttrib4dvNV(index, v);
}
PFNGLVERTEXATTRIB4DVNVPROC glad_glVertexAttrib4dvNV = glad_on_demand_impl_glVertexAttrib4dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC) glad_gl_on_demand_loader("glVertexAttrib4f");
    glad_glVertexAttrib4f(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f = glad_on_demand_impl_glVertexAttrib4f;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glVertexAttrib4fARB = (PFNGLVERTEXATTRIB4FARBPROC) glad_gl_on_demand_loader("glVertexAttrib4fARB");
    glad_glVertexAttrib4fARB(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4FARBPROC glad_glVertexAttrib4fARB = glad_on_demand_impl_glVertexAttrib4fARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glad_glVertexAttrib4fNV = (PFNGLVERTEXATTRIB4FNVPROC) glad_gl_on_demand_loader("glVertexAttrib4fNV");
    glad_glVertexAttrib4fNV(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4FNVPROC glad_glVertexAttrib4fNV = glad_on_demand_impl_glVertexAttrib4fNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4fv(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC) glad_gl_on_demand_loader("glVertexAttrib4fv");
    glad_glVertexAttrib4fv(index, v);
}
PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv = glad_on_demand_impl_glVertexAttrib4fv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4fvARB(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib4fvARB = (PFNGLVERTEXATTRIB4FVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4fvARB");
    glad_glVertexAttrib4fvARB(index, v);
}
PFNGLVERTEXATTRIB4FVARBPROC glad_glVertexAttrib4fvARB = glad_on_demand_impl_glVertexAttrib4fvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4fvNV(GLuint index, const GLfloat * v) {
    glad_glVertexAttrib4fvNV = (PFNGLVERTEXATTRIB4FVNVPROC) glad_gl_on_demand_loader("glVertexAttrib4fvNV");
    glad_glVertexAttrib4fvNV(index, v);
}
PFNGLVERTEXATTRIB4FVNVPROC glad_glVertexAttrib4fvNV = glad_on_demand_impl_glVertexAttrib4fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4iv(GLuint index, const GLint * v) {
    glad_glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC) glad_gl_on_demand_loader("glVertexAttrib4iv");
    glad_glVertexAttrib4iv(index, v);
}
PFNGLVERTEXATTRIB4IVPROC glad_glVertexAttrib4iv = glad_on_demand_impl_glVertexAttrib4iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4ivARB(GLuint index, const GLint * v) {
    glad_glVertexAttrib4ivARB = (PFNGLVERTEXATTRIB4IVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4ivARB");
    glad_glVertexAttrib4ivARB(index, v);
}
PFNGLVERTEXATTRIB4IVARBPROC glad_glVertexAttrib4ivARB = glad_on_demand_impl_glVertexAttrib4ivARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {
    glad_glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC) glad_gl_on_demand_loader("glVertexAttrib4s");
    glad_glVertexAttrib4s(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4SPROC glad_glVertexAttrib4s = glad_on_demand_impl_glVertexAttrib4s;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4sARB(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {
    glad_glVertexAttrib4sARB = (PFNGLVERTEXATTRIB4SARBPROC) glad_gl_on_demand_loader("glVertexAttrib4sARB");
    glad_glVertexAttrib4sARB(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4SARBPROC glad_glVertexAttrib4sARB = glad_on_demand_impl_glVertexAttrib4sARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4sNV(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {
    glad_glVertexAttrib4sNV = (PFNGLVERTEXATTRIB4SNVPROC) glad_gl_on_demand_loader("glVertexAttrib4sNV");
    glad_glVertexAttrib4sNV(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4SNVPROC glad_glVertexAttrib4sNV = glad_on_demand_impl_glVertexAttrib4sNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4sv(GLuint index, const GLshort * v) {
    glad_glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC) glad_gl_on_demand_loader("glVertexAttrib4sv");
    glad_glVertexAttrib4sv(index, v);
}
PFNGLVERTEXATTRIB4SVPROC glad_glVertexAttrib4sv = glad_on_demand_impl_glVertexAttrib4sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4svARB(GLuint index, const GLshort * v) {
    glad_glVertexAttrib4svARB = (PFNGLVERTEXATTRIB4SVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4svARB");
    glad_glVertexAttrib4svARB(index, v);
}
PFNGLVERTEXATTRIB4SVARBPROC glad_glVertexAttrib4svARB = glad_on_demand_impl_glVertexAttrib4svARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4svNV(GLuint index, const GLshort * v) {
    glad_glVertexAttrib4svNV = (PFNGLVERTEXATTRIB4SVNVPROC) glad_gl_on_demand_loader("glVertexAttrib4svNV");
    glad_glVertexAttrib4svNV(index, v);
}
PFNGLVERTEXATTRIB4SVNVPROC glad_glVertexAttrib4svNV = glad_on_demand_impl_glVertexAttrib4svNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4ubNV(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {
    glad_glVertexAttrib4ubNV = (PFNGLVERTEXATTRIB4UBNVPROC) glad_gl_on_demand_loader("glVertexAttrib4ubNV");
    glad_glVertexAttrib4ubNV(index, x, y, z, w);
}
PFNGLVERTEXATTRIB4UBNVPROC glad_glVertexAttrib4ubNV = glad_on_demand_impl_glVertexAttrib4ubNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4ubv(GLuint index, const GLubyte * v) {
    glad_glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC) glad_gl_on_demand_loader("glVertexAttrib4ubv");
    glad_glVertexAttrib4ubv(index, v);
}
PFNGLVERTEXATTRIB4UBVPROC glad_glVertexAttrib4ubv = glad_on_demand_impl_glVertexAttrib4ubv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4ubvARB(GLuint index, const GLubyte * v) {
    glad_glVertexAttrib4ubvARB = (PFNGLVERTEXATTRIB4UBVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4ubvARB");
    glad_glVertexAttrib4ubvARB(index, v);
}
PFNGLVERTEXATTRIB4UBVARBPROC glad_glVertexAttrib4ubvARB = glad_on_demand_impl_glVertexAttrib4ubvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4ubvNV(GLuint index, const GLubyte * v) {
    glad_glVertexAttrib4ubvNV = (PFNGLVERTEXATTRIB4UBVNVPROC) glad_gl_on_demand_loader("glVertexAttrib4ubvNV");
    glad_glVertexAttrib4ubvNV(index, v);
}
PFNGLVERTEXATTRIB4UBVNVPROC glad_glVertexAttrib4ubvNV = glad_on_demand_impl_glVertexAttrib4ubvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC) glad_gl_on_demand_loader("glVertexAttrib4uiv");
    glad_glVertexAttrib4uiv(index, v);
}
PFNGLVERTEXATTRIB4UIVPROC glad_glVertexAttrib4uiv = glad_on_demand_impl_glVertexAttrib4uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4uivARB(GLuint index, const GLuint * v) {
    glad_glVertexAttrib4uivARB = (PFNGLVERTEXATTRIB4UIVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4uivARB");
    glad_glVertexAttrib4uivARB(index, v);
}
PFNGLVERTEXATTRIB4UIVARBPROC glad_glVertexAttrib4uivARB = glad_on_demand_impl_glVertexAttrib4uivARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4usv(GLuint index, const GLushort * v) {
    glad_glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC) glad_gl_on_demand_loader("glVertexAttrib4usv");
    glad_glVertexAttrib4usv(index, v);
}
PFNGLVERTEXATTRIB4USVPROC glad_glVertexAttrib4usv = glad_on_demand_impl_glVertexAttrib4usv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttrib4usvARB(GLuint index, const GLushort * v) {
    glad_glVertexAttrib4usvARB = (PFNGLVERTEXATTRIB4USVARBPROC) glad_gl_on_demand_loader("glVertexAttrib4usvARB");
    glad_glVertexAttrib4usvARB(index, v);
}
PFNGLVERTEXATTRIB4USVARBPROC glad_glVertexAttrib4usvARB = glad_on_demand_impl_glVertexAttrib4usvARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribDivisor(GLuint index, GLuint divisor) {
    glad_glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) glad_gl_on_demand_loader("glVertexAttribDivisor");
    glad_glVertexAttribDivisor(index, divisor);
}
PFNGLVERTEXATTRIBDIVISORPROC glad_glVertexAttribDivisor = glad_on_demand_impl_glVertexAttribDivisor;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribDivisorARB(GLuint index, GLuint divisor) {
    glad_glVertexAttribDivisorARB = (PFNGLVERTEXATTRIBDIVISORARBPROC) glad_gl_on_demand_loader("glVertexAttribDivisorARB");
    glad_glVertexAttribDivisorARB(index, divisor);
}
PFNGLVERTEXATTRIBDIVISORARBPROC glad_glVertexAttribDivisorARB = glad_on_demand_impl_glVertexAttribDivisorARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1i(GLuint index, GLint x) {
    glad_glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC) glad_gl_on_demand_loader("glVertexAttribI1i");
    glad_glVertexAttribI1i(index, x);
}
PFNGLVERTEXATTRIBI1IPROC glad_glVertexAttribI1i = glad_on_demand_impl_glVertexAttribI1i;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1iEXT(GLuint index, GLint x) {
    glad_glVertexAttribI1iEXT = (PFNGLVERTEXATTRIBI1IEXTPROC) glad_gl_on_demand_loader("glVertexAttribI1iEXT");
    glad_glVertexAttribI1iEXT(index, x);
}
PFNGLVERTEXATTRIBI1IEXTPROC glad_glVertexAttribI1iEXT = glad_on_demand_impl_glVertexAttribI1iEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1iv(GLuint index, const GLint * v) {
    glad_glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC) glad_gl_on_demand_loader("glVertexAttribI1iv");
    glad_glVertexAttribI1iv(index, v);
}
PFNGLVERTEXATTRIBI1IVPROC glad_glVertexAttribI1iv = glad_on_demand_impl_glVertexAttribI1iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1ivEXT(GLuint index, const GLint * v) {
    glad_glVertexAttribI1ivEXT = (PFNGLVERTEXATTRIBI1IVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI1ivEXT");
    glad_glVertexAttribI1ivEXT(index, v);
}
PFNGLVERTEXATTRIBI1IVEXTPROC glad_glVertexAttribI1ivEXT = glad_on_demand_impl_glVertexAttribI1ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1ui(GLuint index, GLuint x) {
    glad_glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC) glad_gl_on_demand_loader("glVertexAttribI1ui");
    glad_glVertexAttribI1ui(index, x);
}
PFNGLVERTEXATTRIBI1UIPROC glad_glVertexAttribI1ui = glad_on_demand_impl_glVertexAttribI1ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1uiEXT(GLuint index, GLuint x) {
    glad_glVertexAttribI1uiEXT = (PFNGLVERTEXATTRIBI1UIEXTPROC) glad_gl_on_demand_loader("glVertexAttribI1uiEXT");
    glad_glVertexAttribI1uiEXT(index, x);
}
PFNGLVERTEXATTRIBI1UIEXTPROC glad_glVertexAttribI1uiEXT = glad_on_demand_impl_glVertexAttribI1uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC) glad_gl_on_demand_loader("glVertexAttribI1uiv");
    glad_glVertexAttribI1uiv(index, v);
}
PFNGLVERTEXATTRIBI1UIVPROC glad_glVertexAttribI1uiv = glad_on_demand_impl_glVertexAttribI1uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI1uivEXT(GLuint index, const GLuint * v) {
    glad_glVertexAttribI1uivEXT = (PFNGLVERTEXATTRIBI1UIVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI1uivEXT");
    glad_glVertexAttribI1uivEXT(index, v);
}
PFNGLVERTEXATTRIBI1UIVEXTPROC glad_glVertexAttribI1uivEXT = glad_on_demand_impl_glVertexAttribI1uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2i(GLuint index, GLint x, GLint y) {
    glad_glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC) glad_gl_on_demand_loader("glVertexAttribI2i");
    glad_glVertexAttribI2i(index, x, y);
}
PFNGLVERTEXATTRIBI2IPROC glad_glVertexAttribI2i = glad_on_demand_impl_glVertexAttribI2i;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2iEXT(GLuint index, GLint x, GLint y) {
    glad_glVertexAttribI2iEXT = (PFNGLVERTEXATTRIBI2IEXTPROC) glad_gl_on_demand_loader("glVertexAttribI2iEXT");
    glad_glVertexAttribI2iEXT(index, x, y);
}
PFNGLVERTEXATTRIBI2IEXTPROC glad_glVertexAttribI2iEXT = glad_on_demand_impl_glVertexAttribI2iEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2iv(GLuint index, const GLint * v) {
    glad_glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC) glad_gl_on_demand_loader("glVertexAttribI2iv");
    glad_glVertexAttribI2iv(index, v);
}
PFNGLVERTEXATTRIBI2IVPROC glad_glVertexAttribI2iv = glad_on_demand_impl_glVertexAttribI2iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2ivEXT(GLuint index, const GLint * v) {
    glad_glVertexAttribI2ivEXT = (PFNGLVERTEXATTRIBI2IVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI2ivEXT");
    glad_glVertexAttribI2ivEXT(index, v);
}
PFNGLVERTEXATTRIBI2IVEXTPROC glad_glVertexAttribI2ivEXT = glad_on_demand_impl_glVertexAttribI2ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2ui(GLuint index, GLuint x, GLuint y) {
    glad_glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC) glad_gl_on_demand_loader("glVertexAttribI2ui");
    glad_glVertexAttribI2ui(index, x, y);
}
PFNGLVERTEXATTRIBI2UIPROC glad_glVertexAttribI2ui = glad_on_demand_impl_glVertexAttribI2ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2uiEXT(GLuint index, GLuint x, GLuint y) {
    glad_glVertexAttribI2uiEXT = (PFNGLVERTEXATTRIBI2UIEXTPROC) glad_gl_on_demand_loader("glVertexAttribI2uiEXT");
    glad_glVertexAttribI2uiEXT(index, x, y);
}
PFNGLVERTEXATTRIBI2UIEXTPROC glad_glVertexAttribI2uiEXT = glad_on_demand_impl_glVertexAttribI2uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC) glad_gl_on_demand_loader("glVertexAttribI2uiv");
    glad_glVertexAttribI2uiv(index, v);
}
PFNGLVERTEXATTRIBI2UIVPROC glad_glVertexAttribI2uiv = glad_on_demand_impl_glVertexAttribI2uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI2uivEXT(GLuint index, const GLuint * v) {
    glad_glVertexAttribI2uivEXT = (PFNGLVERTEXATTRIBI2UIVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI2uivEXT");
    glad_glVertexAttribI2uivEXT(index, v);
}
PFNGLVERTEXATTRIBI2UIVEXTPROC glad_glVertexAttribI2uivEXT = glad_on_demand_impl_glVertexAttribI2uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) {
    glad_glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC) glad_gl_on_demand_loader("glVertexAttribI3i");
    glad_glVertexAttribI3i(index, x, y, z);
}
PFNGLVERTEXATTRIBI3IPROC glad_glVertexAttribI3i = glad_on_demand_impl_glVertexAttribI3i;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3iEXT(GLuint index, GLint x, GLint y, GLint z) {
    glad_glVertexAttribI3iEXT = (PFNGLVERTEXATTRIBI3IEXTPROC) glad_gl_on_demand_loader("glVertexAttribI3iEXT");
    glad_glVertexAttribI3iEXT(index, x, y, z);
}
PFNGLVERTEXATTRIBI3IEXTPROC glad_glVertexAttribI3iEXT = glad_on_demand_impl_glVertexAttribI3iEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3iv(GLuint index, const GLint * v) {
    glad_glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC) glad_gl_on_demand_loader("glVertexAttribI3iv");
    glad_glVertexAttribI3iv(index, v);
}
PFNGLVERTEXATTRIBI3IVPROC glad_glVertexAttribI3iv = glad_on_demand_impl_glVertexAttribI3iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3ivEXT(GLuint index, const GLint * v) {
    glad_glVertexAttribI3ivEXT = (PFNGLVERTEXATTRIBI3IVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI3ivEXT");
    glad_glVertexAttribI3ivEXT(index, v);
}
PFNGLVERTEXATTRIBI3IVEXTPROC glad_glVertexAttribI3ivEXT = glad_on_demand_impl_glVertexAttribI3ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) {
    glad_glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC) glad_gl_on_demand_loader("glVertexAttribI3ui");
    glad_glVertexAttribI3ui(index, x, y, z);
}
PFNGLVERTEXATTRIBI3UIPROC glad_glVertexAttribI3ui = glad_on_demand_impl_glVertexAttribI3ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3uiEXT(GLuint index, GLuint x, GLuint y, GLuint z) {
    glad_glVertexAttribI3uiEXT = (PFNGLVERTEXATTRIBI3UIEXTPROC) glad_gl_on_demand_loader("glVertexAttribI3uiEXT");
    glad_glVertexAttribI3uiEXT(index, x, y, z);
}
PFNGLVERTEXATTRIBI3UIEXTPROC glad_glVertexAttribI3uiEXT = glad_on_demand_impl_glVertexAttribI3uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC) glad_gl_on_demand_loader("glVertexAttribI3uiv");
    glad_glVertexAttribI3uiv(index, v);
}
PFNGLVERTEXATTRIBI3UIVPROC glad_glVertexAttribI3uiv = glad_on_demand_impl_glVertexAttribI3uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI3uivEXT(GLuint index, const GLuint * v) {
    glad_glVertexAttribI3uivEXT = (PFNGLVERTEXATTRIBI3UIVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI3uivEXT");
    glad_glVertexAttribI3uivEXT(index, v);
}
PFNGLVERTEXATTRIBI3UIVEXTPROC glad_glVertexAttribI3uivEXT = glad_on_demand_impl_glVertexAttribI3uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4bv(GLuint index, const GLbyte * v) {
    glad_glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC) glad_gl_on_demand_loader("glVertexAttribI4bv");
    glad_glVertexAttribI4bv(index, v);
}
PFNGLVERTEXATTRIBI4BVPROC glad_glVertexAttribI4bv = glad_on_demand_impl_glVertexAttribI4bv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4bvEXT(GLuint index, const GLbyte * v) {
    glad_glVertexAttribI4bvEXT = (PFNGLVERTEXATTRIBI4BVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI4bvEXT");
    glad_glVertexAttribI4bvEXT(index, v);
}
PFNGLVERTEXATTRIBI4BVEXTPROC glad_glVertexAttribI4bvEXT = glad_on_demand_impl_glVertexAttribI4bvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) {
    glad_glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC) glad_gl_on_demand_loader("glVertexAttribI4i");
    glad_glVertexAttribI4i(index, x, y, z, w);
}
PFNGLVERTEXATTRIBI4IPROC glad_glVertexAttribI4i = glad_on_demand_impl_glVertexAttribI4i;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4iEXT(GLuint index, GLint x, GLint y, GLint z, GLint w) {
    glad_glVertexAttribI4iEXT = (PFNGLVERTEXATTRIBI4IEXTPROC) glad_gl_on_demand_loader("glVertexAttribI4iEXT");
    glad_glVertexAttribI4iEXT(index, x, y, z, w);
}
PFNGLVERTEXATTRIBI4IEXTPROC glad_glVertexAttribI4iEXT = glad_on_demand_impl_glVertexAttribI4iEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4iv(GLuint index, const GLint * v) {
    glad_glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC) glad_gl_on_demand_loader("glVertexAttribI4iv");
    glad_glVertexAttribI4iv(index, v);
}
PFNGLVERTEXATTRIBI4IVPROC glad_glVertexAttribI4iv = glad_on_demand_impl_glVertexAttribI4iv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4ivEXT(GLuint index, const GLint * v) {
    glad_glVertexAttribI4ivEXT = (PFNGLVERTEXATTRIBI4IVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI4ivEXT");
    glad_glVertexAttribI4ivEXT(index, v);
}
PFNGLVERTEXATTRIBI4IVEXTPROC glad_glVertexAttribI4ivEXT = glad_on_demand_impl_glVertexAttribI4ivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4sv(GLuint index, const GLshort * v) {
    glad_glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC) glad_gl_on_demand_loader("glVertexAttribI4sv");
    glad_glVertexAttribI4sv(index, v);
}
PFNGLVERTEXATTRIBI4SVPROC glad_glVertexAttribI4sv = glad_on_demand_impl_glVertexAttribI4sv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4svEXT(GLuint index, const GLshort * v) {
    glad_glVertexAttribI4svEXT = (PFNGLVERTEXATTRIBI4SVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI4svEXT");
    glad_glVertexAttribI4svEXT(index, v);
}
PFNGLVERTEXATTRIBI4SVEXTPROC glad_glVertexAttribI4svEXT = glad_on_demand_impl_glVertexAttribI4svEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4ubv(GLuint index, const GLubyte * v) {
    glad_glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC) glad_gl_on_demand_loader("glVertexAttribI4ubv");
    glad_glVertexAttribI4ubv(index, v);
}
PFNGLVERTEXATTRIBI4UBVPROC glad_glVertexAttribI4ubv = glad_on_demand_impl_glVertexAttribI4ubv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4ubvEXT(GLuint index, const GLubyte * v) {
    glad_glVertexAttribI4ubvEXT = (PFNGLVERTEXATTRIBI4UBVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI4ubvEXT");
    glad_glVertexAttribI4ubvEXT(index, v);
}
PFNGLVERTEXATTRIBI4UBVEXTPROC glad_glVertexAttribI4ubvEXT = glad_on_demand_impl_glVertexAttribI4ubvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
    glad_glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC) glad_gl_on_demand_loader("glVertexAttribI4ui");
    glad_glVertexAttribI4ui(index, x, y, z, w);
}
PFNGLVERTEXATTRIBI4UIPROC glad_glVertexAttribI4ui = glad_on_demand_impl_glVertexAttribI4ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4uiEXT(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
    glad_glVertexAttribI4uiEXT = (PFNGLVERTEXATTRIBI4UIEXTPROC) glad_gl_on_demand_loader("glVertexAttribI4uiEXT");
    glad_glVertexAttribI4uiEXT(index, x, y, z, w);
}
PFNGLVERTEXATTRIBI4UIEXTPROC glad_glVertexAttribI4uiEXT = glad_on_demand_impl_glVertexAttribI4uiEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4uiv(GLuint index, const GLuint * v) {
    glad_glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC) glad_gl_on_demand_loader("glVertexAttribI4uiv");
    glad_glVertexAttribI4uiv(index, v);
}
PFNGLVERTEXATTRIBI4UIVPROC glad_glVertexAttribI4uiv = glad_on_demand_impl_glVertexAttribI4uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4uivEXT(GLuint index, const GLuint * v) {
    glad_glVertexAttribI4uivEXT = (PFNGLVERTEXATTRIBI4UIVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI4uivEXT");
    glad_glVertexAttribI4uivEXT(index, v);
}
PFNGLVERTEXATTRIBI4UIVEXTPROC glad_glVertexAttribI4uivEXT = glad_on_demand_impl_glVertexAttribI4uivEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4usv(GLuint index, const GLushort * v) {
    glad_glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC) glad_gl_on_demand_loader("glVertexAttribI4usv");
    glad_glVertexAttribI4usv(index, v);
}
PFNGLVERTEXATTRIBI4USVPROC glad_glVertexAttribI4usv = glad_on_demand_impl_glVertexAttribI4usv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribI4usvEXT(GLuint index, const GLushort * v) {
    glad_glVertexAttribI4usvEXT = (PFNGLVERTEXATTRIBI4USVEXTPROC) glad_gl_on_demand_loader("glVertexAttribI4usvEXT");
    glad_glVertexAttribI4usvEXT(index, v);
}
PFNGLVERTEXATTRIBI4USVEXTPROC glad_glVertexAttribI4usvEXT = glad_on_demand_impl_glVertexAttribI4usvEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer) {
    glad_glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) glad_gl_on_demand_loader("glVertexAttribIPointer");
    glad_glVertexAttribIPointer(index, size, type, stride, pointer);
}
PFNGLVERTEXATTRIBIPOINTERPROC glad_glVertexAttribIPointer = glad_on_demand_impl_glVertexAttribIPointer;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribIPointerEXT(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer) {
    glad_glVertexAttribIPointerEXT = (PFNGLVERTEXATTRIBIPOINTEREXTPROC) glad_gl_on_demand_loader("glVertexAttribIPointerEXT");
    glad_glVertexAttribIPointerEXT(index, size, type, stride, pointer);
}
PFNGLVERTEXATTRIBIPOINTEREXTPROC glad_glVertexAttribIPointerEXT = glad_on_demand_impl_glVertexAttribIPointerEXT;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
    glad_glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC) glad_gl_on_demand_loader("glVertexAttribP1ui");
    glad_glVertexAttribP1ui(index, type, normalized, value);
}
PFNGLVERTEXATTRIBP1UIPROC glad_glVertexAttribP1ui = glad_on_demand_impl_glVertexAttribP1ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) {
    glad_glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC) glad_gl_on_demand_loader("glVertexAttribP1uiv");
    glad_glVertexAttribP1uiv(index, type, normalized, value);
}
PFNGLVERTEXATTRIBP1UIVPROC glad_glVertexAttribP1uiv = glad_on_demand_impl_glVertexAttribP1uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
    glad_glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC) glad_gl_on_demand_loader("glVertexAttribP2ui");
    glad_glVertexAttribP2ui(index, type, normalized, value);
}
PFNGLVERTEXATTRIBP2UIPROC glad_glVertexAttribP2ui = glad_on_demand_impl_glVertexAttribP2ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) {
    glad_glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC) glad_gl_on_demand_loader("glVertexAttribP2uiv");
    glad_glVertexAttribP2uiv(index, type, normalized, value);
}
PFNGLVERTEXATTRIBP2UIVPROC glad_glVertexAttribP2uiv = glad_on_demand_impl_glVertexAttribP2uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
    glad_glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC) glad_gl_on_demand_loader("glVertexAttribP3ui");
    glad_glVertexAttribP3ui(index, type, normalized, value);
}
PFNGLVERTEXATTRIBP3UIPROC glad_glVertexAttribP3ui = glad_on_demand_impl_glVertexAttribP3ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) {
    glad_glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC) glad_gl_on_demand_loader("glVertexAttribP3uiv");
    glad_glVertexAttribP3uiv(index, type, normalized, value);
}
PFNGLVERTEXATTRIBP3UIVPROC glad_glVertexAttribP3uiv = glad_on_demand_impl_glVertexAttribP3uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
    glad_glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC) glad_gl_on_demand_loader("glVertexAttribP4ui");
    glad_glVertexAttribP4ui(index, type, normalized, value);
}
PFNGLVERTEXATTRIBP4UIPROC glad_glVertexAttribP4ui = glad_on_demand_impl_glVertexAttribP4ui;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) {
    glad_glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC) glad_gl_on_demand_loader("glVertexAttribP4uiv");
    glad_glVertexAttribP4uiv(index, type, normalized, value);
}
PFNGLVERTEXATTRIBP4UIVPROC glad_glVertexAttribP4uiv = glad_on_demand_impl_glVertexAttribP4uiv;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer) {
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) glad_gl_on_demand_loader("glVertexAttribPointer");
    glad_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = glad_on_demand_impl_glVertexAttribPointer;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribPointerARB(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer) {
    glad_glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC) glad_gl_on_demand_loader("glVertexAttribPointerARB");
    glad_glVertexAttribPointerARB(index, size, type, normalized, stride, pointer);
}
PFNGLVERTEXATTRIBPOINTERARBPROC glad_glVertexAttribPointerARB = glad_on_demand_impl_glVertexAttribPointerARB;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribPointerNV(GLuint index, GLint fsize, GLenum type, GLsizei stride, const void * pointer) {
    glad_glVertexAttribPointerNV = (PFNGLVERTEXATTRIBPOINTERNVPROC) glad_gl_on_demand_loader("glVertexAttribPointerNV");
    glad_glVertexAttribPointerNV(index, fsize, type, stride, pointer);
}
PFNGLVERTEXATTRIBPOINTERNVPROC glad_glVertexAttribPointerNV = glad_on_demand_impl_glVertexAttribPointerNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs1dvNV(GLuint index, GLsizei count, const GLdouble * v) {
    glad_glVertexAttribs1dvNV = (PFNGLVERTEXATTRIBS1DVNVPROC) glad_gl_on_demand_loader("glVertexAttribs1dvNV");
    glad_glVertexAttribs1dvNV(index, count, v);
}
PFNGLVERTEXATTRIBS1DVNVPROC glad_glVertexAttribs1dvNV = glad_on_demand_impl_glVertexAttribs1dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs1fvNV(GLuint index, GLsizei count, const GLfloat * v) {
    glad_glVertexAttribs1fvNV = (PFNGLVERTEXATTRIBS1FVNVPROC) glad_gl_on_demand_loader("glVertexAttribs1fvNV");
    glad_glVertexAttribs1fvNV(index, count, v);
}
PFNGLVERTEXATTRIBS1FVNVPROC glad_glVertexAttribs1fvNV = glad_on_demand_impl_glVertexAttribs1fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs1svNV(GLuint index, GLsizei count, const GLshort * v) {
    glad_glVertexAttribs1svNV = (PFNGLVERTEXATTRIBS1SVNVPROC) glad_gl_on_demand_loader("glVertexAttribs1svNV");
    glad_glVertexAttribs1svNV(index, count, v);
}
PFNGLVERTEXATTRIBS1SVNVPROC glad_glVertexAttribs1svNV = glad_on_demand_impl_glVertexAttribs1svNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs2dvNV(GLuint index, GLsizei count, const GLdouble * v) {
    glad_glVertexAttribs2dvNV = (PFNGLVERTEXATTRIBS2DVNVPROC) glad_gl_on_demand_loader("glVertexAttribs2dvNV");
    glad_glVertexAttribs2dvNV(index, count, v);
}
PFNGLVERTEXATTRIBS2DVNVPROC glad_glVertexAttribs2dvNV = glad_on_demand_impl_glVertexAttribs2dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs2fvNV(GLuint index, GLsizei count, const GLfloat * v) {
    glad_glVertexAttribs2fvNV = (PFNGLVERTEXATTRIBS2FVNVPROC) glad_gl_on_demand_loader("glVertexAttribs2fvNV");
    glad_glVertexAttribs2fvNV(index, count, v);
}
PFNGLVERTEXATTRIBS2FVNVPROC glad_glVertexAttribs2fvNV = glad_on_demand_impl_glVertexAttribs2fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs2svNV(GLuint index, GLsizei count, const GLshort * v) {
    glad_glVertexAttribs2svNV = (PFNGLVERTEXATTRIBS2SVNVPROC) glad_gl_on_demand_loader("glVertexAttribs2svNV");
    glad_glVertexAttribs2svNV(index, count, v);
}
PFNGLVERTEXATTRIBS2SVNVPROC glad_glVertexAttribs2svNV = glad_on_demand_impl_glVertexAttribs2svNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs3dvNV(GLuint index, GLsizei count, const GLdouble * v) {
    glad_glVertexAttribs3dvNV = (PFNGLVERTEXATTRIBS3DVNVPROC) glad_gl_on_demand_loader("glVertexAttribs3dvNV");
    glad_glVertexAttribs3dvNV(index, count, v);
}
PFNGLVERTEXATTRIBS3DVNVPROC glad_glVertexAttribs3dvNV = glad_on_demand_impl_glVertexAttribs3dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs3fvNV(GLuint index, GLsizei count, const GLfloat * v) {
    glad_glVertexAttribs3fvNV = (PFNGLVERTEXATTRIBS3FVNVPROC) glad_gl_on_demand_loader("glVertexAttribs3fvNV");
    glad_glVertexAttribs3fvNV(index, count, v);
}
PFNGLVERTEXATTRIBS3FVNVPROC glad_glVertexAttribs3fvNV = glad_on_demand_impl_glVertexAttribs3fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs3svNV(GLuint index, GLsizei count, const GLshort * v) {
    glad_glVertexAttribs3svNV = (PFNGLVERTEXATTRIBS3SVNVPROC) glad_gl_on_demand_loader("glVertexAttribs3svNV");
    glad_glVertexAttribs3svNV(index, count, v);
}
PFNGLVERTEXATTRIBS3SVNVPROC glad_glVertexAttribs3svNV = glad_on_demand_impl_glVertexAttribs3svNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs4dvNV(GLuint index, GLsizei count, const GLdouble * v) {
    glad_glVertexAttribs4dvNV = (PFNGLVERTEXATTRIBS4DVNVPROC) glad_gl_on_demand_loader("glVertexAttribs4dvNV");
    glad_glVertexAttribs4dvNV(index, count, v);
}
PFNGLVERTEXATTRIBS4DVNVPROC glad_glVertexAttribs4dvNV = glad_on_demand_impl_glVertexAttribs4dvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs4fvNV(GLuint index, GLsizei count, const GLfloat * v) {
    glad_glVertexAttribs4fvNV = (PFNGLVERTEXATTRIBS4FVNVPROC) glad_gl_on_demand_loader("glVertexAttribs4fvNV");
    glad_glVertexAttribs4fvNV(index, count, v);
}
PFNGLVERTEXATTRIBS4FVNVPROC glad_glVertexAttribs4fvNV = glad_on_demand_impl_glVertexAttribs4fvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs4svNV(GLuint index, GLsizei count, const GLshort * v) {
    glad_glVertexAttribs4svNV = (PFNGLVERTEXATTRIBS4SVNVPROC) glad_gl_on_demand_loader("glVertexAttribs4svNV");
    glad_glVertexAttribs4svNV(index, count, v);
}
PFNGLVERTEXATTRIBS4SVNVPROC glad_glVertexAttribs4svNV = glad_on_demand_impl_glVertexAttribs4svNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexAttribs4ubvNV(GLuint index, GLsizei count, const GLubyte * v) {
    glad_glVertexAttribs4ubvNV = (PFNGLVERTEXATTRIBS4UBVNVPROC) glad_gl_on_demand_loader("glVertexAttribs4ubvNV");
    glad_glVertexAttribs4ubvNV(index, count, v);
}
PFNGLVERTEXATTRIBS4UBVNVPROC glad_glVertexAttribs4ubvNV = glad_on_demand_impl_glVertexAttribs4ubvNV;
static void GLAD_API_PTR glad_on_demand_impl_glVertexPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void * pointer) {
    glad_glVertexPointerEXT = (PFNGLVERTEXPOINTEREXTPROC) glad_gl_on_demand_loader("glVertexPointerEXT");
    glad_glVertexPointerEXT(size, type, stride, count, pointer);
}
PFNGLVERTEXPOINTEREXTPROC glad_glVertexPointerEXT = glad_on_demand_impl_glVertexPointerEXT;
static void GLAD_API_PTR glad_on_demand_impl_glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    glad_glViewport = (PFNGLVIEWPORTPROC) glad_gl_on_demand_loader("glViewport");
    glad_glViewport(x, y, width, height);
}
PFNGLVIEWPORTPROC glad_glViewport = glad_on_demand_impl_glViewport;
static void GLAD_API_PTR glad_on_demand_impl_glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {
    glad_glWaitSync = (PFNGLWAITSYNCPROC) glad_gl_on_demand_loader("glWaitSync");
    glad_glWaitSync(sync, flags, timeout);
}
PFNGLWAITSYNCPROC glad_glWaitSync = glad_on_demand_impl_glWaitSync;


 

#ifdef GLAD_GL

#ifndef GLAD_LOADER_LIBRARY_C_
#define GLAD_LOADER_LIBRARY_C_

#include <stddef.h>
#include <stdlib.h>

#if GLAD_PLATFORM_WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


static void* glad_get_dlopen_handle(const char *lib_names[], int length) {
    void *handle = NULL;
    int i;

    for (i = 0; i < length; ++i) {
#if GLAD_PLATFORM_WIN32
  #if GLAD_PLATFORM_UWP
        size_t buffer_size = (strlen(lib_names[i]) + 1) * sizeof(WCHAR);
        LPWSTR buffer = (LPWSTR) malloc(buffer_size);
        if (buffer != NULL) {
            int ret = MultiByteToWideChar(CP_ACP, 0, lib_names[i], -1, buffer, buffer_size);
            if (ret != 0) {
                handle = (void*) LoadPackagedLibrary(buffer, 0);
            }
            free((void*) buffer);
        }
  #else
        handle = (void*) LoadLibraryA(lib_names[i]);
  #endif
#else
        handle = dlopen(lib_names[i], RTLD_LAZY | RTLD_LOCAL);
#endif
        if (handle != NULL) {
            return handle;
        }
    }

    return NULL;
}

static void glad_close_dlopen_handle(void* handle) {
    if (handle != NULL) {
#if GLAD_PLATFORM_WIN32
        FreeLibrary((HMODULE) handle);
#else
        dlclose(handle);
#endif
    }
}

static GLADapiproc glad_dlsym_handle(void* handle, const char *name) {
    if (handle == NULL) {
        return NULL;
    }

#if GLAD_PLATFORM_WIN32
    return (GLADapiproc) GetProcAddress((HMODULE) handle, name);
#else
    return GLAD_GNUC_EXTENSION (GLADapiproc) dlsym(handle, name);
#endif
}

#endif /* GLAD_LOADER_LIBRARY_C_ */

typedef void* (GLAD_API_PTR *GLADglprocaddrfunc)(const char*);
struct _glad_gl_userptr {
    void *handle;
    GLADglprocaddrfunc gl_get_proc_address_ptr;
};

static GLADapiproc glad_gl_get_proc(void *vuserptr, const char *name) {
    struct _glad_gl_userptr userptr = *(struct _glad_gl_userptr*) vuserptr;
    GLADapiproc result = NULL;

    if(userptr.gl_get_proc_address_ptr != NULL) {
        result = GLAD_GNUC_EXTENSION (GLADapiproc) userptr.gl_get_proc_address_ptr(name);
    }
    if(result == NULL) {
        result = glad_dlsym_handle(userptr.handle, name);
    }

    return result;
}

static void* _glad_GL_loader_handle = NULL;

static void* glad_gl_dlopen_handle(void) {
#if GLAD_PLATFORM_APPLE
    static const char *NAMES[] = {
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
    };
#elif GLAD_PLATFORM_WIN32
    static const char *NAMES[] = {"opengl32.dll"};
#else
    static const char *NAMES[] = {
  #if defined(__CYGWIN__)
        "libGL-1.so",
  #endif
        "libGL.so.1",
        "libGL.so",
        "libEGL.so.1",
        "libEGL.so"
    };
#endif

    if (_glad_GL_loader_handle == NULL) {
        _glad_GL_loader_handle = glad_get_dlopen_handle(NAMES, sizeof(NAMES) / sizeof(NAMES[0]));
    }

    return _glad_GL_loader_handle;
}

static struct _glad_gl_userptr glad_gl_build_userptr(void *handle) {
    struct _glad_gl_userptr userptr;

    userptr.handle = handle;
#if GLAD_PLATFORM_APPLE || defined(__HAIKU__)
    userptr.gl_get_proc_address_ptr = NULL;
#elif GLAD_PLATFORM_WIN32
    userptr.gl_get_proc_address_ptr =
        (GLADglprocaddrfunc) glad_dlsym_handle(handle, "wglGetProcAddress");
#else
    userptr.gl_get_proc_address_ptr =
        (GLADglprocaddrfunc) glad_dlsym_handle(handle, "glXGetProcAddressARB");
    if (!userptr.gl_get_proc_address_ptr)
        userptr.gl_get_proc_address_ptr =
            (GLADglprocaddrfunc) glad_dlsym_handle(handle, "eglGetProcAddress");
#endif

    return userptr;
}


#ifdef __cplusplus
static struct _glad_gl_userptr glad_gl_internal_loader_global_userptr = {};
#else
static struct _glad_gl_userptr glad_gl_internal_loader_global_userptr = { 0 };
#endif
static GLADapiproc glad_gl_internal_loader_get_proc(const char *name) {
    if (glad_gl_internal_loader_global_userptr.handle == NULL) {
        glad_gl_internal_loader_global_userptr = glad_gl_build_userptr(glad_gl_dlopen_handle());
    }

    return glad_gl_get_proc((void *) &glad_gl_internal_loader_global_userptr, name);
}


void gladLoaderUnloadGL(void) {
    if (_glad_GL_loader_handle != NULL) {
        glad_close_dlopen_handle(_glad_GL_loader_handle);
        _glad_GL_loader_handle = NULL;
        glad_gl_internal_loader_global_userptr.handle = NULL;
    }
}

#endif /* GLAD_GL */

#ifdef __cplusplus
}
#endif
