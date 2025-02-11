import 'package:flutter/material.dart';
import 'ui/media_editor.dart';
import 'Properties.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  Properties.init().then((dir) {
    runApp(const MyApp());
  });
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    const primaryColor = Color(0xffd91818);
    return MaterialApp(
      title: 'FilmKilns',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(
          seedColor: primaryColor,
          primary: primaryColor,
        ),
        useMaterial3: true,
      ),
      home: const MediaEditorPage(title: '编辑', fixedCameraPage: true),
    );
  }
}
