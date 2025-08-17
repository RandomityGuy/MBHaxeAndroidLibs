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

    public native static void importPrefs(String prefsData);

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

    private static final int REQ_EXPORT_PREFS = 1001;
    private static final int REQ_IMPORT_JSON = 5001;

    public static void exportPrefsJson() {
        if (instance == null) return;
        java.io.File prefs = new java.io.File(instance.getFilesDir(), "prefs.json");
        if (!prefs.exists()) return;
        Intent intent = new Intent(Intent.ACTION_CREATE_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("application/json");
        intent.putExtra(Intent.EXTRA_TITLE, "prefs.json");
        instance.startActivityForResult(intent, REQ_EXPORT_PREFS);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQ_EXPORT_PREFS && resultCode == Activity.RESULT_OK && data != null) {
            Uri uri = data.getData();
            if (uri == null) return;
            java.io.File src = new java.io.File(getFilesDir(), "prefs.json");
            java.io.FileInputStream in = null;
            java.io.OutputStream out = null;
            try {
                in = new java.io.FileInputStream(src);
                out = getContentResolver().openOutputStream(uri);
                if (out == null) return;
                byte[] buf = new byte[8192];
                int n;
                while ((n = in.read(buf)) != -1) out.write(buf, 0, n);
                out.flush();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try { if (in != null) in.close(); } catch (Exception ignored) {}
                try { if (out != null) out.close(); } catch (Exception ignored) {}
            }
        }
        if (requestCode == REQ_IMPORT_JSON && resultCode == Activity.RESULT_OK && data != null) {
        Uri uri = data.getData();
        if (uri != null) {
            try (java.io.InputStream in = getContentResolver().openInputStream(uri);
                 java.io.ByteArrayOutputStream baos = new java.io.ByteArrayOutputStream()) {
                if (in != null) {
                    byte[] buf = new byte[8192];
                    int n;
                    while ((n = in.read(buf)) != -1) baos.write(buf, 0, n);
                    importedJsonContent = baos.toString("UTF-8");
                    importPrefs(importedJsonContent);
                }
            } catch (Exception e) {
                importedJsonContent = null;
                importPrefs(importedJsonContent);
            }
        }
    }
    }

    // Import JSON support
    private static String importedJsonContent;
    public static String getImportedJsonContent() {
        return importedJsonContent;
    }
    public static void importJsonFile() {
        if (instance == null) return;
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("application/json");
        instance.startActivityForResult(intent, REQ_IMPORT_JSON);
    }
}
