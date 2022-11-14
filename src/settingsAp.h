#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <PubSubClient.h>
#include "_config.h"
#include "memory.h"

class SettingsAp {
private:
	Memory _memory;
	WebServer _server;
public:
	void sendHtml();
	void getData();
	void initAp(Memory& x);
};

const char settingsPage1[] PROGMEM = R"=====(<!DOCTYPE html>
<html lang='en'>
  <head>
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Настройки</title>
    <style>
      html {
        font-family: Tahoma;
      }
      body {
        margin: 0 auto;
        width: 90%;
        min-width: 200px;
      }
      @media (min-aspect-ratio: 3/4) {
        body {
          width: 50%;
          min-width: 67.5vh;
        }
      }
      h4 {
        margin-top: 40px;
      }
      dt {
        float: left;
        width: 200px;
        text-align: right;
        padding-right: 5px;
        min-height: 1px;
      }
      dd {
        position: relative;
        top: -1px;
        margin-bottom: 10px;
      }
      .formFields {
        text-align: center;
        display: flex;
        justify-content: space-around;
        flex-wrap: wrap;
      }
      .formField {
        margin: 10px 15px;
      }
    </style>

    <script>
      var )=====";

const char settingsPage2[] PROGMEM = R"=====(

      window.onload = function() {
        if (wifi === '') {
          document.getElementsByName('ssid')[0].required = true;
          document.getElementsByName('pass')[0].required = true;
          document.getElementsByName('mqtt')[0].required = true;
        }
        else {
          document.getElementsByName('ssid')[0].placeholder='Added, can be changed';
          document.getElementsByName('pass')[0].placeholder='Added, can be changed';
          document.getElementsByName('mqtt')[0].placeholder='Added, can be changed';
          document.getElementsByName('ssid')[0].value=wifi;
          document.getElementsByName('mqtt')[0].value=mqtt;
          document.querySelectorAll('select')[0].getElementsByTagName('option')[type].selected = true;
        }
      }
    </script>
  </head>

  <body>
    <h1>Настройки</h1>
    <form action='/senddata' method='post' onsubmit='alert("The settings will now be applied and the controller will restart...");' id="filters">
      <div class='formFields'>
        <div class='formField'><label>WiFi network name</label><br>
        <input placeholder='Should be entered' name='ssid'></div>

        <div class='formField'><label>WiFi Password</label><br>
        <input placeholder='Should be entered' type='password' name='pass'></div>

        <div class='formField'><label>MQTT server (IP or link)</label><br>
        <input placeholder='Should be entered' name='mqtt'></div>

        <div class='formField'><label>Sensors count:</label><br>
        <select name='hours'>
          <option selected value='6'>Minimum (6 pins)</option>
          <option value='13'>Extended (13 pins)</option>
        </select></div>

        <div class='formField'><input type='submit' value='Save'></div>
      </div>
    </form>

    <br>
    <h4>Опрос датчиков</h4>
    Minimum: 6 pins are used, the controller is always connected to WiFi.
    <br>
    Advanced: 13 pins are used, the controller disconnects from WiFi for a period of time to retrieve data from the pins.
  </body>
</html>)=====";