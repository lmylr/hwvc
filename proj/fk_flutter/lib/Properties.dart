import 'dart:io';
import 'dart:ffi';
import 'package:path_provider/path_provider.dart';

base class CArray extends Struct {
  external Pointer<Uint8> data;
  @Int32()
  external int len;
}

class Properties {
  static late Directory appDocumentsDirectory;
  static late Directory appCacheDirectory;
  static late Directory appDraftDirectory;

  static Future init() async {
    appDocumentsDirectory = await getApplicationCacheDirectory();
    appCacheDirectory = await getApplicationCacheDirectory();
    appDraftDirectory = Directory("${appCacheDirectory.path}/draft");
    if (!appDraftDirectory.existsSync()) {
      appDraftDirectory.createSync(recursive: true);
    }
  }
}