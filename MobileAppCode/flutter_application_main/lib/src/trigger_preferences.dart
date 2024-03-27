import 'package:flutter/material.dart';


class TriggerPreferencesPage extends StatelessWidget {
  const TriggerPreferencesPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Set Trigger Preferences'),
      ),
      body: Center(
        child: Column(
          children: [
            ElevatedButton(
              onPressed: () {
               Navigator.pop(context);
              },
            child: const Text('Set GPS Location Trigger'),
            ),
          
            ElevatedButton(
              onPressed: () {
               Navigator.pop(context);
              },
            child: const Text('Set Audio Trigger'),
            ),
            ElevatedButton(
              onPressed: () {
               Navigator.pop(context);
              },
            child: const Text('Set Button Trigger'),
            ),
            ElevatedButton(
              onPressed: () {
               Navigator.pop(context);
              },
            child: const Text('Set Separation Trigger'),
            ),
            ElevatedButton(
              onPressed: () {
               Navigator.pop(context);
              },
            child: const Text('Go back!'),
            ),
          ],
        ),
      ),
    );
  }
}