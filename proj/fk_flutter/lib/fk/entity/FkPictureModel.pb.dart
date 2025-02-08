//
//  Generated code. Do not modify.
//  source: FkPictureModel.proto
//
// @dart = 2.12

// ignore_for_file: annotate_overrides, camel_case_types, comment_references
// ignore_for_file: constant_identifier_names, library_prefixes
// ignore_for_file: non_constant_identifier_names, prefer_final_fields
// ignore_for_file: unnecessary_import, unnecessary_this, unused_import

import 'dart:core' as $core;

import 'package:protobuf/protobuf.dart' as $pb;

import 'FkImageLayer.pb.dart' as $5;

class FkPictureModel extends $pb.GeneratedMessage {
  factory FkPictureModel({
    $5.FkImageLayer? canvas,
    $core.Iterable<$5.FkImageLayer>? layers,
  }) {
    final $result = create();
    if (canvas != null) {
      $result.canvas = canvas;
    }
    if (layers != null) {
      $result.layers.addAll(layers);
    }
    return $result;
  }
  FkPictureModel._() : super();
  factory FkPictureModel.fromBuffer($core.List<$core.int> i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromBuffer(i, r);
  factory FkPictureModel.fromJson($core.String i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromJson(i, r);

  static final $pb.BuilderInfo _i = $pb.BuilderInfo(_omitMessageNames ? '' : 'FkPictureModel', package: const $pb.PackageName(_omitMessageNames ? '' : 'com.alimin.fk.pb'), createEmptyInstance: create)
    ..aOM<$5.FkImageLayer>(1, _omitFieldNames ? '' : 'canvas', subBuilder: $5.FkImageLayer.create)
    ..pc<$5.FkImageLayer>(2, _omitFieldNames ? '' : 'layers', $pb.PbFieldType.PM, subBuilder: $5.FkImageLayer.create)
    ..hasRequiredFields = false
  ;

  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.deepCopy] instead. '
  'Will be removed in next major version')
  FkPictureModel clone() => FkPictureModel()..mergeFromMessage(this);
  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.rebuild] instead. '
  'Will be removed in next major version')
  FkPictureModel copyWith(void Function(FkPictureModel) updates) => super.copyWith((message) => updates(message as FkPictureModel)) as FkPictureModel;

  $pb.BuilderInfo get info_ => _i;

  @$core.pragma('dart2js:noInline')
  static FkPictureModel create() => FkPictureModel._();
  FkPictureModel createEmptyInstance() => create();
  static $pb.PbList<FkPictureModel> createRepeated() => $pb.PbList<FkPictureModel>();
  @$core.pragma('dart2js:noInline')
  static FkPictureModel getDefault() => _defaultInstance ??= $pb.GeneratedMessage.$_defaultFor<FkPictureModel>(create);
  static FkPictureModel? _defaultInstance;

  @$pb.TagNumber(1)
  $5.FkImageLayer get canvas => $_getN(0);
  @$pb.TagNumber(1)
  set canvas($5.FkImageLayer v) { setField(1, v); }
  @$pb.TagNumber(1)
  $core.bool hasCanvas() => $_has(0);
  @$pb.TagNumber(1)
  void clearCanvas() => clearField(1);
  @$pb.TagNumber(1)
  $5.FkImageLayer ensureCanvas() => $_ensure(0);

  @$pb.TagNumber(2)
  $core.List<$5.FkImageLayer> get layers => $_getList(1);
}


const _omitFieldNames = $core.bool.fromEnvironment('protobuf.omit_field_names');
const _omitMessageNames = $core.bool.fromEnvironment('protobuf.omit_message_names');
