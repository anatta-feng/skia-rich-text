#include <jni.h>
#include <string>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include <android/log.h>

#include "SkBitmap.h"
#include "include/core/SkFont.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkRect.h"
#include "include/core/SkColor.h"
#include "include/core/SkGraphics.h"

#define TAG "LIB_RENDER"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

ANativeWindow *window;

std::string jstringToString(JNIEnv *env, jstring jstr) {
    const char *cstr = env->GetStringUTFChars(jstr, nullptr);
    std::string result(cstr);
    env->ReleaseStringUTFChars(jstr, cstr);
    return result;
}

extern "C" {
JNIEXPORT jint JNICALL
Java_com_vaipixel_librender_PixelCanvas_setupSurface(JNIEnv *env, jobject thiz, jobject surface) {
    window = ANativeWindow_fromSurface(env, surface);
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_vaipixel_librender_PixelCanvas_release(JNIEnv *env, jobject thiz) {
    ANativeWindow_release(window);
    return 0;
}

}
extern "C"
JNIEXPORT jint JNICALL
Java_com_vaipixel_librender_PixelCanvas_drawText(JNIEnv *env, jobject thiz, jstring text) {

    const char *str = env->GetStringUTFChars(text, NULL);

    LOGD("draw text: %s", str);

    ANativeWindow_setBuffersGeometry(window, 100, 100, WINDOW_FORMAT_RGBA_8888);

    ANativeWindow_Buffer *buffer = new ANativeWindow_Buffer();
    ANativeWindow_lock(window, buffer, 0);
    int bpr = buffer->stride * 4;

    SkBitmap bitmap;
    SkImageInfo imageInfo = SkImageInfo::MakeS32(buffer->width, buffer->height,
                                                 SkAlphaType::kPremul_SkAlphaType);

    bitmap.setInfo(imageInfo, bpr);
    bitmap.setPixels(buffer->bits);

    SkCanvas *background = new SkCanvas(bitmap);
    SkPaint paint;

    paint.setColor(SK_ColorGREEN);
    SkRect rect;
    rect.set(SkIRect::MakeWH(100, 100));

    background->drawRect(rect, paint);

    SkPaint paint2;
    paint2.setColor(SK_ColorWHITE);
    SkFont skFont(SkTypeface::MakeDefault(), 30);
    background->drawString(str, 0, 30, skFont, paint2);

    ANativeWindow_unlockAndPost(window);
    return 0;
}