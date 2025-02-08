import 'dart:ffi';
import 'dart:io';

class FilmKilnsLibs {
  static FilmKilnsLibs? _instance;
  final _libFkAndroidName = 'libFkAndroid.so';
  final _libFilmKilnsName = 'libFilmKilns.so';
  static DynamicLibrary? _libFkAndroid;
  static DynamicLibrary? _libFilmKilns;

  FilmKilnsLibs._internal();

  static FilmKilnsLibs getInstance() {
    _instance ??= FilmKilnsLibs._internal();
    return _instance!;
  }

  DynamicLibrary libFkAndroid() {
    _libFkAndroid ??= Platform.isAndroid
        ? DynamicLibrary.open(_libFkAndroidName)
        : DynamicLibrary.process();
    return _libFkAndroid!;
  }

  DynamicLibrary libFilmKilns() {
    _libFilmKilns ??= Platform.isAndroid
        ? DynamicLibrary.open(_libFilmKilnsName)
        : DynamicLibrary.process();
    return _libFilmKilns!;
  }
}
