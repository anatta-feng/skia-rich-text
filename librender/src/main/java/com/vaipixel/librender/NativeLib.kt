package com.vaipixel.librender

class NativeLib {

    /**
     * A native method that is implemented by the 'librender' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'librender' library on application startup.
        init {
            System.loadLibrary("librender")
        }
    }
}