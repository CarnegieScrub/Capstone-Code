import 'package:flutter/material.dart';
import 'src/emergency_contact.dart';
import 'src/pickContacts.dart';
import 'src/trigger_preferences.dart';
import 'src/bluetooth.dart';


//Logo from here: https://clipart-library.com/clipart/8TG64o7qc.htm

void main() {
  runApp( MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'Guardian Companion App'),
    ));
}

class MyHomePage extends StatelessWidget {
  const MyHomePage({super.key, required this.title});
  final String title;
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(title),
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
      ),
      body:  Center(
        // Center is a layout widget. It takes a single child and positions it
        // in the middle of the parent.
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Image.asset('images/TempGuardian2.png',width: 500, height: 500,scale: 0.5),
            SizedBox( width: 250, height: 50,
              child: ElevatedButton(
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) =>  PickContactsPage()),
                );
              },

              child:  const Text('Set Emergency Contacts'),
              ),
            ),
             const SizedBox( width: 250, height: 20,
            ),
            SizedBox( width: 250, height: 50,
              child: ElevatedButton(
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) =>  TriggerPreferencesPage()),
                );
              },
              child:  const Text('Set Trigger Preferences'),
              ),
            ),
            const SizedBox( width: 250, height: 20),
            SizedBox( width: 250, height: 50,
              child: ElevatedButton(
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) =>  FlutterBlueApp()),
                );
              },
              child:  const Text('Connect to Bluetooth'),
              ),
            )

            
          ],
        ),
      ),
    );
  }
}

// class SecondRoute extends StatelessWidget {
//   const SecondRoute({super.key});

//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: const Text('Second Route'),
//       ),
//       body: Center(
//         child: ElevatedButton(
//           onPressed: () {
//             Navigator.pop(context);
//           },
//           child: const Text('Go back!'),
//         ),
//       ),
//     );
//   }
// }