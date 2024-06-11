package org.haxe;

import org.libsdl.app.SDLActivity;
import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.content.SharedPreferences;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

public class HashLinkActivity extends SDLActivity {
    private static HashLinkActivity instance;

    public static native int startHL();

    public native static void initAssets(AssetManager assetManager, String strDir);

    // Used to load the native libraries on application startup.
    static {
        System.loadLibrary("openal");
        System.loadLibrary("SDL2");
        System.loadLibrary("heapsapp");
    }

    @Override
    protected String getMainFunction() {
        return "main";
    }

    @Override
    protected void onCreate(Bundle state) {
        super.onCreate(state);
        instance = this;
        // 初始化Assets对象
        initAssets(getAssets(), getFilesDir().getAbsolutePath());
    }

    @Override
    protected String[] getLibraries() {
        return new String[] {
                "openal",
                "SDL2",
                "heapsapp"
        };
    }

    protected void run() {
        super.run();
        this.startHL();
    }

    static public void saveData(String name, String data) {
        SharedPreferences sharedPref = getContext().getSharedPreferences(name, Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPref.edit();
        editor.putString(name, data);
        editor.apply();
    }

    static public String loadData(String name) {
        SharedPreferences sharedPref = getContext().getSharedPreferences(name, Context.MODE_PRIVATE);
        return sharedPref.getString(name, "null");
    }

    public static Context getContext() {
        return instance.getApplicationContext();
    }

    public static void openWebURL(String url) {
        Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
        instance.startActivity(browserIntent);
    }
}
