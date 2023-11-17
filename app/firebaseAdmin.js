
// var admin = require("firebase-admin");

// var serviceAccount = {
//     "type": "service_account",
//     "project_id": "fullstack-iot-web",
//     "private_key_id": process.env.FIREBASE_PRIVATE_KEY_ID,
//     "private_key": process.env.FIREBASE_PRIVATE_KEY
//     ? JSON.parse(process.env.FIREBASE_PRIVATE_KEY)
//     : undefined,
//     "client_email": "firebase-adminsdk-hp71q@fullstack-iot-web.iam.gserviceaccount.com",
//     "client_id": "108722940011939426120",
//     "auth_uri": "https://accounts.google.com/o/oauth2/auth",
//     "token_uri": "https://oauth2.googleapis.com/token",
//     "auth_provider_x509_cert_url": "https://www.googleapis.com/oauth2/v1/certs",
//     "client_x509_cert_url": "https://www.googleapis.com/robot/v1/metadata/x509/firebase-adminsdk-hp71q%40fullstack-iot-web.iam.gserviceaccount.com",
//     "universe_domain": "googleapis.com"
// }
// console.log(serviceAccount);

// admin.initializeApp({
//   credential: admin.credential.cert(serviceAccount),
//   storageBucket: "fullstack-iot-web.appspot.com",
//   databaseURL: "https://fullstack-iot-web-default-rtdb.firebaseio.com"
// });

// const db = admin.firestore();
// const auth = admin.auth();
// const storage = admin.storage();

// export {db, auth, admin, storage}


// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAuth } from "firebase/auth";

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyAmoJ66G3mH61Pv2Spn-ypNHQOgS-Oe6bg",
  authDomain: "iotstruggle.firebaseapp.com",
  databaseURL: "https://iotstruggle-default-rtdb.firebaseio.com",
  projectId: "iotstruggle",
  storageBucket: "iotstruggle.appspot.com",
  messagingSenderId: "81579355665",
  appId: "1:81579355665:web:5705836824bf1844074bb0",
  measurementId: "G-MLJT3MDZXR"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
export const auth = getAuth(app);
