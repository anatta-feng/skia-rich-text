package com.vaipixel.librender

import android.content.Context
import android.util.AttributeSet
import android.util.Log
import android.view.SurfaceHolder
import android.view.SurfaceView

class SkiaPlayer : SurfaceView, SurfaceHolder.Callback2 {
    constructor(context: Context) : super(context) {
        setupSurface()
    }

    constructor(context: Context, attrs: AttributeSet) : super(context, attrs) {
        setupSurface()
    }

    private val canvas: PixelCanvas by lazy { PixelCanvas() }

    private fun setupSurface() {
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        Log.d(TAG, "surfaceCreated: 1")
        canvas.setupSurface(holder.surface)
        Log.d(TAG, "surfaceCreated: 2")
        canvas.drawText("Hello")
        Log.d(TAG, "surfaceCreated: 3")
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
    }

    override fun surfaceRedrawNeeded(holder: SurfaceHolder) {
    }

    companion object {
        private const val TAG = "SkiaPlayer"
    }
}