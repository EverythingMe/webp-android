package me.everything.webp;

import android.graphics.Bitmap;

import java.nio.ByteBuffer;

public class WebPDecoder {
    private static WebPDecoder instance = null;

    private WebPDecoder() {
        System.loadLibrary("webp_evme");
    }

    public static WebPDecoder getInstance() {
        if (instance == null) {
            synchronized (WebPDecoder.class) {
                if (instance == null) {
                    instance = new WebPDecoder();
                }
            }
        }

        return instance;
    }

    public Bitmap decodeWebP(byte[] encoded) {
        int[] width = new int[]{0};
        int[] height = new int[]{0};

        byte[] decoded = decodeRGBAnative(encoded, encoded.length, width, height);
        if (decoded.length == 0) return null;

        int[] pixels = new int[decoded.length / 4];
        ByteBuffer.wrap(decoded).asIntBuffer().get(pixels);

        return Bitmap.createBitmap(pixels, width[0], height[0], Bitmap.Config.ARGB_8888);
    }

    public static native byte[] decodeRGBAnative(byte[] encoded, long encodedLength, int[] width, int[] height);
}
