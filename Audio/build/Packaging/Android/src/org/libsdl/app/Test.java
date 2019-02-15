package org.libsdl.app;

import android.util.Log;

public class Test
{
	public static void testLog() {
		Log.e("SDL", "Test.testLog()");
	}

	public static int test1(String myString) {
		Log.e("SDL", "Test.test1(" + myString + ")");
		return 42;
	}

	public static int test2(int myInt) {
		Log.e("SDL", "Test.test2(" +  Integer.toString(myInt) + ")");
		return 43;
	}

	public static int test3(int myInt, float myFloat) {
		Log.e("SDL", "Test.test3(" +  Integer.toString(myInt) + "," + Float.toString(myFloat) + ")");
		return 44;
	}

	public static int test4(int myInt, boolean myBoolean) {
		Log.e("SDL", "Test.test4(" +  Integer.toString(myInt) + "," + Boolean.toString(myBoolean) + ")");
		return 45;
	}

	public static boolean test5(int myInt) {
		Log.e("SDL", "Test.test5(" +  Integer.toString(myInt) + ")");
		return true;
	}
}
