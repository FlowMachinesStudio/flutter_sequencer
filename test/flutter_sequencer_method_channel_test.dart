import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_sequencer/flutter_sequencer_method_channel.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  // ignore: omit_local_variable_types
  MethodChannelFlutterSequencer platform = MethodChannelFlutterSequencer();
  // ignore: omit_local_variable_types
  const MethodChannel channel = MethodChannel('flutter_sequencer');

  setUp(() {
    TestDefaultBinaryMessengerBinding.instance?.defaultBinaryMessenger
        .setMockMethodCallHandler(
      channel,
      (MethodCall methodCall) async {
        return '42';
      },
    );
  });

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance?.defaultBinaryMessenger
        .setMockMethodCallHandler(channel, null);
  });

  test('getPlatformVersion', () async {
    expect(await platform.getPlatformVersion(), '42');
  });
}
