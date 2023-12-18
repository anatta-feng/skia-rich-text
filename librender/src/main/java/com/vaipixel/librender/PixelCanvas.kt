package com.vaipixel.librender

import android.view.Surface

class PixelCanvas {

    external fun setupSurface(surface: Surface): Int

    external fun release(): Int

    external fun drawText(text: String): Int

    companion object {
        // Used to load the 'lib-render' library on application startup.
        init {
            System.loadLibrary("render")
        }
    }
}