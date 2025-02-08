import 'package:flutter/material.dart';

class DialogUtils {
  static void showLoading(BuildContext context, final String text) {
    showDialog(
      barrierDismissible:false,
      barrierColor: Colors.grey,
      context: context,
      builder: (context) {
        return AlertDialog(
          content: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              const CircularProgressIndicator(),
              Padding(
                padding: const EdgeInsets.only(top: 8),
                child: Text(text),
              )
            ],
          ),
        );
      },
    );
  }
}
