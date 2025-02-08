import 'package:flutter/material.dart';
import 'package:fk_flutter/utils/dialog_utils.dart';
import 'package:image_picker/image_picker.dart';

typedef ImageResultCallback = void Function(XFile? file);

class SystemUtils {
  static void pickImage(BuildContext context, ImageResultCallback callback) {
    DialogUtils.showLoading(context, "Loading");
    final picker = ImagePicker();
    final image = picker.pickImage(source: ImageSource.gallery);
    image.then((file) {
      callback(file);
      Navigator.of(context).pop();
    });
  }
}
