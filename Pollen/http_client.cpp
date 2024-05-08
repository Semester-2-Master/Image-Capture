#include <AsyncHTTPRequest_Generic.h>
#include "esp_camera.h"
// #include "time_config.h"

AsyncHTTPRequest request;

void sendRequest()
{
  static bool requestOpenResult;

  if (request.readyState() == readyStateUnsent || request.readyState() == readyStateDone)
  {
    requestOpenResult = request.open("POST", "http://192.168.1.171:5194/image");

    if (requestOpenResult)
    {
      request.setTimeout(100);
      request.setReqHeader("Content-Type", "image/jpeg");
      camera_fb_t *fb = esp_camera_fb_get();
      request.send(fb->buf, fb->len);
      esp_camera_fb_return(fb);
    }
    else
    {
      Serial.println("Can't send bad request");
    }
  }
  else
  {
    Serial.println("Can't send request");
  }
}

void requestCB(void *optParm, AsyncHTTPRequest *request, int readyState)
{
  Serial.println("Upload done");
  // (void) optParm;

  // if (readyState == readyStateDone)
  // {
  //   AHTTP_LOGDEBUG(F("\n**************************************"));
  //   AHTTP_LOGDEBUG1(F("Response Code = "), request->responseHTTPString());

  //   if (request->responseHTTPcode() == 200)
  //   {
  //     Serial.println(F("\n**************************************"));
  //     Serial.println(request->responseText());
  //     Serial.println(F("**************************************"));
  //   }
  // }
}

void init_client() {
  request.onReadyStateChange(requestCB);
}

// void post_picture() {
//   if (WiFi.status() == WL_CONNECTED) {
//     if (client.connect(serverName.c_str(), port)) {
//       Serial.println("Connection successful!");

//       camera_fb_t *fb = esp_camera_fb_get();
//       if (!fb) {
//         Serial.println("Failed to capture image");
//         return;
//       }

//       const size_t maxTimeBufferSize = 30; // Maximum size for the time string buffer
//       char timeBuffer[maxTimeBufferSize]; // Buffer to hold the formatted time string
//     //   Obtain the current time and store it in the time buffer
//       get_time(timeBuffer, maxTimeBufferSize);
//       // Construct the filename with the time string
//       String filename = String(timeBuffer) + ".jpg";

//       String head = "--RandomNerdTutorials\r\nContent-Disposition: form-data; name=\"file\"; filename=\""+filename+"\"\r\nContent-Type: image/jpeg\r\n\r\n";
//       String tail = "\r\n--RandomNerdTutorials--\r\n";
//       size_t imageLen = fb->len;
//       size_t extraLen = head.length() + tail.length();
//       size_t totalLen = imageLen + extraLen;

//       // Send HTTP POST request headers
//       client.println("POST " + serverPath + " HTTP/1.1");
//       client.println("Host: " + serverName + ":" + String(port));
//       client.println("Content-Type: multipart/form-data; boundary=RandomNerdTutorials");
//       client.println("Content-Length: " + String(totalLen));
//       client.println();

//       // Send image data
//       client.print(head);
//       client.write(fb->buf, fb->len);
//       client.print(tail);

//       // Wait for response
//       delay(10); // Allow time for server to process
//       while (client.available()) {
//         char c = client.read();
//         Serial.print(c);
//       }

//       // Clean up
//       client.stop();
//       esp_camera_fb_return(fb);
//     } else {
//       Serial.println("Connection failed!");
//     }
//   }
// }
