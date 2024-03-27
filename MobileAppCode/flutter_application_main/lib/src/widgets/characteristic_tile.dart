import 'dart:async';
import 'dart:math';
import 'dart:typed_data'; // Import for Uint8List

import 'package:flutter/material.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';

import "../utils/snackbar.dart";
import 'dart:convert';
import "descriptor_tile.dart";

class CharacteristicTile extends StatefulWidget {
  final BluetoothCharacteristic characteristic;
  final List<DescriptorTile> descriptorTiles;

  const CharacteristicTile({Key? key, required this.characteristic, required this.descriptorTiles}) : super(key: key);

  @override
  State<CharacteristicTile> createState() => _CharacteristicTileState();
}

class _CharacteristicTileState extends State<CharacteristicTile> {
  List<int> _value = [];

  late StreamSubscription<List<int>> _lastValueSubscription;

  @override
  void initState() {
    super.initState();
    _lastValueSubscription = widget.characteristic.lastValueStream.listen((value) {
      _value = value;
      if (mounted) {
        setState(() {});
      }
    });
  }

  @override
  void dispose() {
    _lastValueSubscription.cancel();
    super.dispose();
  }

  BluetoothCharacteristic get c => widget.characteristic;

  List<int> _getRandomBytes() {
    final math = Random();
    return [math.nextInt(255), math.nextInt(255), math.nextInt(255), math.nextInt(255)];
  }

  List<int> _getPhoneNumberBytes(String number) {
    return utf8.encode(number);
    //return [math.nextInt(255), math.nextInt(255), math.nextInt(255), math.nextInt(255)];
  }
  

  Future onReadPressed() async {
    try {
      await c.read();
      Snackbar.show(ABC.c, "Read: Success", success: true);
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Read Error:", e), success: false);
    }
  }

  Future onWritePressed() async {
    try {
      await c.write(_getRandomBytes(), withoutResponse: c.properties.writeWithoutResponse);
      //await c.write(_getPhoneNumberBytes(), withoutResponse: c.properties.writeWithoutResponse);
      Snackbar.show(ABC.c, "Write: Success", success: true);
      if (c.properties.read) {
        await c.read();
      }
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Write Error:", e), success: false);
    }
  }
  Future onContactPressed(String number) async {
    try {
      //await c.write(_getRandomBytes(), withoutResponse: c.properties.writeWithoutResponse);
      await c.write(_getPhoneNumberBytes(number), withoutResponse: c.properties.writeWithoutResponse);
      Snackbar.show(ABC.c, "Write: Success", success: true);
      if (c.properties.read) {
        await c.read();
      }
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Write Error:", e), success: false);
    }
  }

  Future onSubscribePressed() async {
    try {
      String op = c.isNotifying == false ? "Subscribe" : "Unubscribe";
      await c.setNotifyValue(c.isNotifying == false);
      Snackbar.show(ABC.c, "$op : Success", success: true);
      if (c.properties.read) {
        await c.read();
      }
      if (mounted) {
        setState(() {});
      }
    } catch (e) {
      Snackbar.show(ABC.c, prettyException("Subscribe Error:", e), success: false);
    }
  }

  Widget buildUuid(BuildContext context) {
    String uuid = '0x${widget.characteristic.uuid.str.toUpperCase()}';
    return Text(uuid, style: TextStyle(fontSize: 13));
  }

  Widget buildValue(BuildContext context) {
    String data = _value.toString();
    return Text(data, style: TextStyle(fontSize: 13, color: Colors.grey));
  }

  Widget buildReadButton(BuildContext context) {
    return TextButton(
        child: Text("Read"),
        onPressed: () async {
          await onReadPressed();
          if (mounted) {
            setState(() {});
          }
        });
  }

  Widget buildWriteButton(BuildContext context) {
    bool withoutResp = widget.characteristic.properties.writeWithoutResponse;
    return TextButton(
        child: Text(withoutResp ? "WriteNoResp" : "Write"),
        onPressed: () async {
          await onWritePressed();
          if (mounted) {
            setState(() {});
          }
        });
  }
  Widget sendContact1(BuildContext context, String number) {
    bool withoutResp = widget.characteristic.properties.writeWithoutResponse;
    //String number = "4087619438";
    return TextButton(
        child: Text(withoutResp ? "WriteNoResp" : "SendC1"),
        onPressed: () async {
          await onContactPressed(number);
          if (mounted) {
            setState(() {});
          }
        });
  }
  Widget sendContact2(BuildContext context, String number) {
    bool withoutResp = widget.characteristic.properties.writeWithoutResponse;
    //String number = "4087619438";
    return TextButton(
        child: Text(withoutResp ? "WriteNoResp" : "SendC2"),
        onPressed: () async {
          await onContactPressed(number);
          if (mounted) {
            setState(() {});
          }
        });
  }
  Widget sendContact3(BuildContext context, String number) {
    bool withoutResp = widget.characteristic.properties.writeWithoutResponse;
    //String number = "4087619438";
    return TextButton(
        child: Text(withoutResp ? "WriteNoResp" : "SendC3"),
        onPressed: () async {
          await onContactPressed(number);
          if (mounted) {
            setState(() {});
          }
        });
  }
  // Widget sendContact2(BuildContext context) {
  //   bool withoutResp = widget.characteristic.properties.writeWithoutResponse;
  //   return TextButton(
  //       child: Text(withoutResp ? "WriteNoResp" : "SendContact1"),
  //       onPressed: () async {
  //         await onContactPressed();
  //         if (mounted) {
  //           setState(() {});
  //         }
  //       });
  // }

  Widget buildSubscribeButton(BuildContext context) {
    bool isNotifying = widget.characteristic.isNotifying;
    return TextButton(
        child: Text(isNotifying ? "Unsubscribe" : "Subscribe"),
        onPressed: () async {
          await onSubscribePressed();
          if (mounted) {
            setState(() {});
          }
        });
  }

  Widget buildButtonRow(BuildContext context) {
    bool read = widget.characteristic.properties.read;
    bool write = widget.characteristic.properties.write;
    bool notify = widget.characteristic.properties.notify;
    bool indicate = widget.characteristic.properties.indicate;
    return Row(
      mainAxisSize: MainAxisSize.min,
      children: [
        if (read) buildReadButton(context),
        //if (write) buildWriteButton(context),
        if (write) sendContact1(context,"4087619438"),
        if (write) sendContact2(context,"1234567890"),
        if (write) sendContact3(context,"9187465324")
        //if (notify || indicate) buildSubscribeButton(context),
      ],
    );
  }

  @override
  Widget build(BuildContext context) {
    return ExpansionTile(
      title: ListTile(
        title: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            const Text('Characteristic'),
            buildUuid(context),
            buildValue(context),
          ],
        ),
        subtitle: buildButtonRow(context),
        contentPadding: const EdgeInsets.all(0.0),
      ),
      children: widget.descriptorTiles,
    );
  }
}
