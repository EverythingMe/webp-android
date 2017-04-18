# webp
## webp for all! (Android devices)

webp is a library we use at EverythingMe Launcher since we love webp. We use it to save bandwidth as well as shrinking our APK sizes.

webp is an adaptation of chromium's webp decoder, and an addition of a JNI wrapper to easily use it it in your java code.

## compile
just `gradle clean build`, and add the output aar to your libs (a public aar will be available soon)

## How to use it?

```java
import me.everything.webp.WebPDecoder

Bitmap bitmap = WebPDecoder.getInstance().decodeWebP(bytes);
```

## WebpImageView
We also made it easy to load webp images from xml to an ImageView

```xml
<me.everything.webp.WebPImageView
  android:layout_width="wrap_content"
  android:layout_height="wrap_content"
  webp:webp_src="@drawable/your_webp_image" />
``` 

Native webp support with lossless and transparency is officially supported in Android 4.2.1 and up. Prior to that transparency was not supported.
Since both 4.2 and 4.2.x have the same API level (17), we apply webp's decoding for all API levels lower than 18. For API level 18 and up we apply the standard `BitmapFactory.decodeByteArray()`.