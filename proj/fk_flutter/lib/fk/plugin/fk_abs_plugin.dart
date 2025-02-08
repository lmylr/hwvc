import 'dart:ffi';
import 'package:ffi/ffi.dart';
import 'package:fk_flutter/fk/fk_libs.dart';
import 'package:fk_flutter/fk/entity/FkPbValue.pb.dart';
import 'package:fk_flutter/fk/entity/FkValueMap.pb.dart';
import 'package:fk_flutter/Properties.dart';

class FkAbsPlugin {
  late final Pointer<Void> _handle;
  late final int Function(Pointer<Void>, Pointer<Uint8>, int) _fUpdateParams;
  late final CArray Function(Pointer<Void>, Pointer<Utf8>) _fGetParam;

  FkAbsPlugin(String name) {
    DynamicLibrary nativeLib = FilmKilnsLibs.getInstance().libFkAndroid();
    final Pointer<Void> Function(Pointer<Utf8>) nativeCreate = nativeLib
        .lookup<NativeFunction<Pointer<Void> Function(Pointer<Utf8>)>>(
            'FkPlugin_create')
        .asFunction();
    _handle = nativeCreate(name.toNativeUtf8());
    _fUpdateParams = nativeLib.lookup<NativeFunction<Int Function(Pointer<Void>, Pointer<Uint8>, Int)>>(
        'FkPlugin_updateParams')
        .asFunction();
    _fGetParam = nativeLib.lookup<NativeFunction<CArray Function(Pointer<Void>, Pointer<Utf8>)>>(
        'FkPlugin_getParam')
        .asFunction();
  }

  Pointer<Void> getHandle() {
    return _handle;
  }

  int updateParams(Map<String, FkPbValue> params) {
    final map = FkValueMap.create();
    map.value.addAll(params);
    final buf = map.writeToBuffer();
    final pointer = malloc.allocate<Uint8>(buf.length);
    pointer.asTypedList(buf.length).setAll(0, buf);
    final ret = _fUpdateParams(_handle, pointer, buf.length);
    malloc.free(pointer);
    return ret;
  }

  FkPbValue? getParam(String key) {
    CArray result = _fGetParam(_handle, key.toNativeUtf8());
    if (result.len <= 0) {
      return null;
    }
    final value = FkPbValue.fromBuffer(result.data.asTypedList(result.len));
    malloc.free(result.data);
    return value;
  }
}
