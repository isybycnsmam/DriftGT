// AUTO-GENERATED ON BUILD
// DO NOT CHANGE
// generated by pre build script '../extra_script.py'
#include <avr/pgmspace.h>
#include "ESPAsyncWebServer.h"

#ifndef STATIC_WEBSITE_CONTENT_H
#define STATIC_WEBSITE_CONTENT_H


const char INDEX_CONTENT[] PROGMEM = R"""(<!doctype html><title>DriftGT</title><meta name=viewport content="width=device-width"><meta name=mobile-web-app-capable content=yes><link rel=stylesheet href=style.css><div class=slider-container><input type=range class="slider vertical-slider" min=-255 max=255 value=0 id=vertical-slider></div><div class=slider-container><input type=range class=slider min=-255 max=255 value=0 id=horizontal-slider></div><div class=settings-container><button id=connect-button>Connect</button> <button id=fullscreen-button>Fullscreen</button> <button id=show-console-button>Console</button> <button id=show-user-controlls-button>Show me bitches</button><div id=user-control-options-container class=hide><button class=user-control-option data-name=arrows data-enabled=false>Enable arrows</button> <button class=user-control-option data-name=WSAD data-enabled=false>Enable WSAD</button> <button class="user-control-option enabled" data-name=touch data-enabled=true>Disable touch</button> <button class=user-control-option data-name=gamepad data-enabled=false>Enable gamepad</button></div></div><div class=features-container><button id=horn-button>Horn</button> <button id=toggle-lights-button>Lights</button></div><script src=./scripts.js></script>)""";

const char SCRIPTS_CONTENT[] PROGMEM = R"""(var a='ws://192.168.4.1:80/ws',b=40,c=1,d=0,e=100,f=180,g=document.getElementById('connect-button'),h=document.getElementById('show-user-controlls-button'),i=document.getElementById('user-control-options-container'),j=document.querySelector('.user-control-option[data-name="gamepad"]'),k=document.getElementById("horn-button"),l=document.getElementById("toggle-lights-button"),m=document.getElementById('vertical-slider'),n=document.getElementById('horizontal-slider'),o,u=!1,v=!1,y=!1,z,_=!1,aE=!1,aF=!1,aG=!1,aH=!1;function p(){console.log("Initializing websocket");console.log("Connecting to websocket");g.innerText="Connecting...";g.style.backgroundColor='#6687E2';o=new WebSocket(a);o.onopen=()=>{console.log("Websocket connected");g.style.backgroundColor='#66E976';g.innerText='Disconnect'};o.onclose=()=>{console.log("Websocket closed");g.style.backgroundColor='#FD616C';g.innerText='Connect*'};console.log("Successfully initialized websocket")}function q(){console.log("Closing websocket");g.innerText="Disconnecting...";g.style.backgroundColor='#6687E2';o.close()}g.onclick=()=>!o||o.readyState==WebSocket.CLOSED?p():o.readyState==WebSocket.OPEN&&q();function r(B,C){if(o?.readyState!==WebSocket.OPEN)return;B=='move'?C.unshift(0):B=='lights'?C.unshift(1):B=='horn'&&C.unshift(2);o.send(new Uint8Array(C))}function s(B,C){var _c=Math.abs(C),D=C>0?3:2;if(_c-b<0){r('move',[B,0,0]);return}B==c&&_c>128&&(_c=f);B==d&&_c>128&&(_c=140);r('move',[B,D,_c])}h.onclick=()=>i.classList.toggle('hide');for(const B of document.querySelectorAll('.user-control-option'))B.onclick=t;function t(B){var C=B.target,_c=C.dataset.name,D=C.dataset.enabled=='true';if(_c=='arrows'||_c=='WSAD')D?aJ(_c):aI(_c); else if(_c=='touch'){n.disabled=D;m.disabled=D;k.disabled=D;l.disabled=D} else if(_c=='gamepad')D?aA():A();else{console.warn(`Unknown option name`,B.target);return}C.dataset.enabled=!D;C.classList.toggle('enabled');C.innerText=!D?'Disable ':'Enable '+_c}function w(){u=!u;u?l.classList.add("enabled"):l.classList.remove("enabled");var B=u?1:0;r('lights',[B])}function x(B){if(v==B)return;v=B;B?k.classList.add("enabled"):k.classList.remove("enabled");r('horn',[B?1:0])}function A(){navigator.getGamepads()[0]&&aB();window.addEventListener("gamepadconnected",aB);window.addEventListener("gamepaddisconnected",aC)}function aA(){window.removeEventListener("gamepadconnected",aB);window.removeEventListener("gamepaddisconnected",aC);aC()}function aB(){console.log("Gamepad connected!");!y&&(y=!0,j.classList.add('active'),z=setInterval(aD,e))}function aC(){console.log("Gamepad disconnected!");y&&(y=!1,j.classList.remove('active'),clearInterval(z))}function aD(){var B=navigator.getGamepads(),C=B[0];if(C){var _a=C.axes[0],_b=Math.round(_a*255),_c=C.buttons[7].value,D=C.buttons[6].value,E=Math.round(_c*255),F=Math.round(D*255),G=C.buttons[0].value,H=C.buttons[1].value;n.value=_b;s(c,_b);E>F?(m.value=E,s(d,E)):(m.value=F*-1,s(d,F*-1));x(G==1);H==1&&!_?(_=!0,w()):(_=!1)}}function aI(B){if(B=='arrows')['keydown','keyup'].forEach(name=>document.addEventListener(name,aL)); else if(B=='WSAD')['keydown','keyup'].forEach(name=>document.addEventListener(name,aK));else{console.log(`Unknown keyboard control option to enable: '${B}'`);return}k.innerText="Horn (space)";l.innerText="Lights (L)"}function aJ(B){if(B=='arrows')['keydown','keyup'].forEach(name=>document.removeEventListener(name,aL)); else if(B=='WSAD')['keydown','keyup'].forEach(name=>document.removeEventListener(name,aK));else{console.log(`Unknown keyboard control option to disable: '${B}'`);return}k.innerText="Horn";l.innerText="Lights"}function aK(B){aM(B);aO(aN(B,'w','s','a','d'))}function aL(B){aM(B);aO(aN(B,'ArrowUp','ArrowDown','ArrowLeft','ArrowRight'))}function aM(B){var C=B.type=='keydown';B.key==' '?x(C):B.key=='l'&&C&&w()}function aN(B,C,_c,D,E){var F=B.key,G=B.type=='keydown';if(F==C){aE=G;return'driving'}if(F==_c){aF=G;return'driving'}if(F==D){aG=G;return'turning'}if(F==E){aH=G;return'turning'}return""}function aO(B){if(B=='driving')if(aE==aF){s(d,0);m.value=0} else if(aE){s(d,255);m.value=255}else aF&&(s(d,-255),m.value=-255);if(B=='turning')if(aG==aH){s(c,0);n.value=0} else if(aH){s(c,255);n.value=255}else aG&&(s(c,-255),n.value=-255)}m.addEventListener('input',()=>s(d,m.value));n.addEventListener('input',()=>s(c,n.value));for(const B of ['mouseup','touchend']){m.addEventListener(B,()=>{m.value=0;s(d,0)});n.addEventListener(B,()=>{n.value=0;s(c,0)})}document.getElementById('fullscreen-button').addEventListener('click',()=>document.body.requestFullscreen());)""";

const char STYLE_CONTENT[] PROGMEM = R"""(body{display:flex;justify-content:center;align-items:center;height:100vh;margin:0;padding:0;font-family:Arial,sans-serif;background-color:#333;color:#fff}.settings-container{position:absolute;top:10px;right:10px;color:#fff}button{color:#fff;border:none;text-align:center;text-decoration:none;display:inline-block;font-size:16px;padding:5px}#connect-button{background-color:#fd616c}#fullscreen-button{background-color:#5f9ea0}#show-console-button{background-color:#222453}#show-user-controlls-button{background-color:#8467e3;width:140px}#user-control-options-container{display:flex;flex-direction:column;align-items:flex-end;width:100%;padding-top:5px}.user-control-option{display:block;margin-right:0;width:140px;background-color:#434343}.user-control-option.enabled{background-color:#5f9ea0}.hide{display:none!important}.user-control-option.enabled[data-name=gamepad]:not(.active){background-color:orange}.features-container{position:absolute;bottom:10px;right:10px;color:#fff}#horn-button{width:130px;background-color:#325a21}#horn-button.enabled{background-color:#509433}#horn-button:disabled{color:#646262}#toggle-lights-button{width:130px;background-color:#425a76}#toggle-lights-button.enabled{background-color:#4a9cff}#toggle-lights-button:disabled{color:#646262}.slider-container{width:40%;height:80%;display:flex;flex-direction:column;justify-content:center;align-items:center;margin-right:8%}.slider{width:100%;position:relative}.vertical-slider{writing-mode:bt-lr;transform:rotate(-90deg);margin-top:10%}.slider::-webkit-slider-thumb{width:60px;height:60px;background-color:#fff;border-radius:50%;position:relative;z-index:9999;transform:translateX(-50%) translateY(-50%) scale(4)!important}.slider::-moz-range-thumb{width:60px;height:60px;background-color:#fff;border-radius:50%;position:relative;z-index:9999;transform:translateX(-50%) translateY(-50%) scale(2)!important}.slider::-ms-thumb{width:60px;height:60px;background-color:#fff;border-radius:50%;position:relative;z-index:9999;transform:translateX(-50%) translateY(-50%) scale(2)!important}.slider::before{content:'';width:100%;height:8px;background-color:#555;position:absolute;top:50%;transform:translateY(-50%);z-index:0}.slider::-webkit-slider-runnable-track{width:100%;height:8px;background-color:#555;position:relative;z-index:0}.slider::-moz-range-track{width:100%;height:8px;background-color:#555;position:relative;z-index:0}.slider::-ms-track{width:100%;height:8px;background-color:#555;position:relative;z-index:0}.slider::-moz-range-progress{height:8px;background-color:#fff;position:relative;z-index:1})""";


void init_static_content_endpoints(AsyncWebServer *server) {
	server->on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(200, "text/html", INDEX_CONTENT); });

	server->on("/scripts.js", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(200, "text/javascript", SCRIPTS_CONTENT); });

	server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(200, "text/css", STYLE_CONTENT); });

}


#endif // STATIC_WEBSITE_CONTENT_H