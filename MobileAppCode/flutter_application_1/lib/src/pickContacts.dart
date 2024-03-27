import 'package:flutter/material.dart';
import 'emergency_contact.dart';

class PickContactsPage extends StatelessWidget {
  const PickContactsPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Set Emergency Contacts'),
      ),
      body: Center(
        child: Column(
          children: [
            ElevatedButton(
          onPressed: () {
            Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) =>  EmergencyContactPage()),
                );
          },
          child: const Text('Set Contact 1'),
        ),
        ElevatedButton(
          onPressed: () {
            Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) =>  EmergencyContactPage()),
                );
          },
          child: const Text('Set Contact 2'),
        ),
        ElevatedButton(
          onPressed: () {
          Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) =>  EmergencyContactPage()),
                );
          },
          child: const Text('Set Contact 3'),
        ),
        ElevatedButton(
          onPressed: () {
            Navigator.pop(context);
          },
          child: const Text('Go back!'),
        ),
        ElevatedButton(
          onPressed: () {
            Navigator.pop(context);
          },
          child: const Text('Send Test Phone Number'),
        ),

          ]
        )
      ),
    );
  }
}