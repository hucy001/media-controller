package com.plutinosoft.platinum;

public class UPnP {
    public UPnP() {
        cSelf = _init();
    }

    public int start() { 
    	String strMR ="640980f6ab5c-dmr";
    	String strMS ="640980f6ab5c-dms";
    	_setRenderId(strMR);
    	_setServerId(strMS);
        return _start(cSelf);
    }
    
    public int stop() {
        return _stop(cSelf);
    }

    // C glue
    private static native long _init();
    private static native int _start(long self);
    private static native int _stop(long self);
    private static native int _setRenderId(String id);
    private static native int _setServerId(String id);
    private final long     cSelf;

    static {
        System.loadLibrary("platinum-jni");
    }
}
