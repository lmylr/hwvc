//
//  Generated code. Do not modify.
//  source: FkImageLayer.proto
//
// @dart = 2.12

// ignore_for_file: annotate_overrides, camel_case_types, comment_references
// ignore_for_file: constant_identifier_names, library_prefixes
// ignore_for_file: non_constant_identifier_names, prefer_final_fields
// ignore_for_file: unnecessary_import, unnecessary_this, unused_import

import 'dart:convert' as $convert;
import 'dart:core' as $core;
import 'dart:typed_data' as $typed_data;

@$core.Deprecated('Use fkImageLayerDescriptor instead')
const FkImageLayer$json = {
  '1': 'FkImageLayer',
  '2': [
    {'1': 'size', '3': 1, '4': 1, '5': 11, '6': '.com.alimin.fk.pb.FkSize', '10': 'size'},
    {'1': 'rotation', '3': 2, '4': 1, '5': 11, '6': '.com.alimin.fk.pb.FkRational', '10': 'rotation'},
    {'1': 'scale', '3': 3, '4': 1, '5': 11, '6': '.com.alimin.fk.pb.FkFloatVec3', '10': 'scale'},
    {'1': 'trans', '3': 4, '4': 1, '5': 11, '6': '.com.alimin.fk.pb.FkDoubleVec3', '10': 'trans'},
    {'1': 'file', '3': 5, '4': 1, '5': 9, '10': 'file'},
    {'1': 'id', '3': 6, '4': 1, '5': 5, '10': 'id'},
    {'1': 'color', '3': 7, '4': 1, '5': 5, '10': 'color'},
    {'1': 'paths', '3': 8, '4': 3, '5': 11, '6': '.com.alimin.fk.pb.FkPaintPath', '10': 'paths'},
  ],
};

/// Descriptor for `FkImageLayer`. Decode as a `google.protobuf.DescriptorProto`.
final $typed_data.Uint8List fkImageLayerDescriptor = $convert.base64Decode(
    'CgxGa0ltYWdlTGF5ZXISLAoEc2l6ZRgBIAEoCzIYLmNvbS5hbGltaW4uZmsucGIuRmtTaXplUg'
    'RzaXplEjgKCHJvdGF0aW9uGAIgASgLMhwuY29tLmFsaW1pbi5may5wYi5Ga1JhdGlvbmFsUghy'
    'b3RhdGlvbhIzCgVzY2FsZRgDIAEoCzIdLmNvbS5hbGltaW4uZmsucGIuRmtGbG9hdFZlYzNSBX'
    'NjYWxlEjQKBXRyYW5zGAQgASgLMh4uY29tLmFsaW1pbi5may5wYi5Ga0RvdWJsZVZlYzNSBXRy'
    'YW5zEhIKBGZpbGUYBSABKAlSBGZpbGUSDgoCaWQYBiABKAVSAmlkEhQKBWNvbG9yGAcgASgFUg'
    'Vjb2xvchIzCgVwYXRocxgIIAMoCzIdLmNvbS5hbGltaW4uZmsucGIuRmtQYWludFBhdGhSBXBh'
    'dGhz');

