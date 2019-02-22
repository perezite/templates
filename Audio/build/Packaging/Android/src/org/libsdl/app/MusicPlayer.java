package org.libsdl.app;

import android.app.Activity;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.util.Log;
import android.media.MediaPlayer;

import java.io.IOException;

public class MusicPlayer implements MediaPlayer.OnCompletionListener, MediaPlayer.OnPreparedListener {
    Activity parentActivity;
    String assetPath;
    private MediaPlayer mediaPlayer = null;
    private boolean isLoaded = false;
    private boolean isPrepared = false;

    public MusicPlayer(String _assetPath, Activity _parentActivity) {
        assetPath = _assetPath;
        parentActivity = _parentActivity;
    }

    public void loadAsync() throws IOException  {
        AssetManager assetManager = parentActivity.getAssets();
        AssetFileDescriptor assetDescriptor = assetManager.openFd(assetPath);

        mediaPlayer = new MediaPlayer();
        mediaPlayer.setDataSource(assetDescriptor.getFileDescriptor(),
                assetDescriptor.getStartOffset(), assetDescriptor.getLength());

        mediaPlayer.setOnCompletionListener(this);
        mediaPlayer.setOnPreparedListener(this);
        mediaPlayer.prepareAsync();
    }

    public boolean isLoadComplete() {
        synchronized (this) {
            return isLoaded;
        }
    }

	public void pause() {
		// mediaPlayer.setVolume(0, 0);	// using mediaPlayer.resume() messes up the pitch of SoundPool for some weird reason, so we use this cheesy trick instead -.-
		mediaPlayer.pause(); 
	}

	public void resume() {
		// mediaPlayer.setVolume(1, 1); // using mediaPlayer.resume() messes up the pitch of SoundPool for some weird reason, so we use this cheesy trick instead -.-
		mediaPlayer.start();
	}

    public void play() throws IOException {
        if (mediaPlayer.isPlaying())
            return;

        synchronized (this) {
            if (!isPrepared) {
                mediaPlayer.prepare();
                isPrepared = true;
            }
        }

        mediaPlayer.start();
    }

    public void stop() {
        mediaPlayer.stop();
        synchronized (this) {
            isPrepared = false;
        }
    }

    public boolean isLooping() {
        return mediaPlayer.isLooping();
    }

    public void setLooping(boolean looping) {
        mediaPlayer.setLooping(looping);
    }

    public void setVolume(float volume) {
        mediaPlayer.setVolume(volume, volume);
    }

    public void release() {
	    synchronized (this) {
			if (isPrepared) {
				mediaPlayer.setLooping(false);
				mediaPlayer.stop();
				mediaPlayer.release();
				isPrepared = false;
			}
        }
		// Log.e("SDL", "MusicPlayer.release(): " + assetPath);
    }

    @Override
    public void onCompletion(MediaPlayer completedMediaPlayer) {
        if (mediaPlayer == completedMediaPlayer) {
            synchronized (this) {
                isPrepared = false;
            }
        }
    }

    @Override
    public void onPrepared(MediaPlayer preparedMediaPlayer) {
        synchronized (this) {
            isLoaded = true;
            isPrepared = true;
        }
    }
}
