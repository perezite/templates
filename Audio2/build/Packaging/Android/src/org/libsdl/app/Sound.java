package org.libsdl.app;

import android.app.Activity;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.media.AudioManager;
import android.media.SoundPool;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

public class Sound {
    static Activity ParentActivity;
    static SoundPool soundPool = null;
    static List<Integer> SoundIds = new ArrayList<Integer>();
    static List<Integer> LoadedSoundIds = new ArrayList<Integer>();

    public static void init(Activity activity) {
        ParentActivity = activity;
        soundPool = new SoundPool(20, AudioManager.STREAM_MUSIC, 0);
    }

    public static int loadAsync(String assetPath) {
        int soundId = -1;

        try {
            AssetManager assetManager = ParentActivity.getAssets();
            AssetFileDescriptor sound1Descriptor = assetManager.openFd(assetPath);
            soundId = soundPool.load(sound1Descriptor, 1);
            SoundIds.add(soundId);
        } catch (Exception e) {
            return -1;
        }

        return soundId;
    }

    public static int isLoadComplete(int soundId) {
        try {
            if (LoadedSoundIds.contains(new Integer(soundId)))
                return 1;

            boolean loadComplete = testIfLoadComplete(soundId);
            if (loadComplete)
                LoadedSoundIds.add(soundId);

            return loadComplete ? 1 : 0;
        } catch(Exception e) {
            return -1;
        }
    }

	public static void pause() {
		for (Integer i : SoundIds)
			soundPool.pause(i);
	}

	public static void resume() {
	    for (Integer i : SoundIds) 
			soundPool.resume(i);
	}

    public static int play(int soundId) {
        try {
            soundPool.play(soundId, 1, 1, 0, 0, 1);
        } catch (Exception e) {
            return -1;
        }

        return 0;
    }

    public static int release(int soundId) {
        try {
            soundPool.unload(soundId);
            SoundIds.remove(new Integer(soundId));
            LoadedSoundIds.remove(new Integer(soundId));
        } catch (Exception e) {
            return -1;
        }

        return 0;
    }

    public static int setVolume(int soundId, float volume) {
        try {
            soundPool.setVolume(soundId, volume, volume);
        } catch (Exception e) {
            return -1;
        }

        return 0;
    }

    public static void release() {
        for (Integer i : SoundIds)
            release(i);

		// Log.e("SDL", "Sound.release()");

    }

    // test if loading the sound has completed, by attempting to play the sound silently
    private static boolean testIfLoadComplete(int soundId) {
        int result = soundPool.play(soundId, 0, 0, 0, 0, 1.0f);
        if (result > 0) {
            soundPool.stop(soundId);
            return true;
        }

        return false;
    }
}
