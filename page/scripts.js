const url = 'ws://192.168.4.1:80/ws';
const speedActivationOffset = 20;
const turningActivationOffset = 20;
const turningMotor = 1;
const speedMotor = 0;
const gamepadRefreshDelayMs = 100;
const maxTurningSpeed = 128;

const connectButton = document.getElementById('connect-button');
const showConsoleButton = document.getElementById('show-console-button');
const showUserControlOptionsButton = document.getElementById('show-user-controlls-button');

const userControlOptionsContainer = document.getElementById('user-control-options-container');
const gamepadControllOptionButton = document.querySelector('.user-control-option[data-name="gamepad"]');

const verticalSlider = document.getElementById('vertical-slider');
const horizontalSlider = document.getElementById('horizontal-slider');


// === managing connection process ===

var websocket;

function openWebSocket() {
    console.log("Initializing websocket");

    console.log("Connecting to websocket");
    connectButton.innerText = "Connecting...";
    connectButton.style.backgroundColor = '#6687E2';

    websocket = new WebSocket(url);
    websocket.onopen = () => {
        console.log("Websocket connected");
        connectButton.style.backgroundColor = '#66E976';
        connectButton.innerText = 'Disconnect';
    }
    websocket.onclose = () => {
        console.log("Websocket closed");
        connectButton.style.backgroundColor = '#FD616C';
        connectButton.innerText = 'Connect*';
    }

    console.log("Successfully initialized websocket");
}

function closeWebSocket() {
    console.log("Closing websocket");
    connectButton.innerText = "Disconnecting...";
    connectButton.style.backgroundColor = '#6687E2';
    websocket.close();
}

connectButton.onclick = () => {
    if (!websocket || websocket.readyState === WebSocket.CLOSED) {
        openWebSocket();
    }
    else if (websocket.readyState === WebSocket.OPEN) {
        closeWebSocket();
    }
}

// === handling driving controlls ===

function handleDrivingCommand(motor, value) {
    if (websocket?.readyState !== WebSocket.OPEN) {
        return;
    }

    var absValue = Math.abs(value);

    if (absValue - turningActivationOffset < 20) {
        // set direction to neutral and motor speed to 0
        websocket.send(`${motor}0000`);
    }

    if (motor === turningMotor && absValue > 128) {
        absValue = maxTurningSpeed;
    } 

    const direction = value > 0 ? '3' : '2'; // 3 - forward, 2 - backward
    const speed = ('000' + absValue).slice(-3);
    const message = `${motor}${direction}${speed}`;

    websocket.send(message);
}


// === handling user control options ===

showUserControlOptionsButton.onclick = () => {
    userControlOptionsContainer.classList.toggle('hide');
}

document.querySelectorAll('.user-control-option').forEach(element => {
    element.onclick = controlOptionChanged;
});

function controlOptionChanged(event) {
    const target = event.target;
    const name = target.dataset.name;
    const isCurrentlyEnabled = target.dataset.enabled == 'true';

    if (name === 'arrows' || name === 'WSAD') {
        if (isCurrentlyEnabled) {
            disableKeyboardControll(name);
        }
        else {
            enableKeyboardControll(name);
        }
    }
    else if (name === 'touch') {
        horizontalSlider.disabled = isCurrentlyEnabled;
        verticalSlider.disabled = isCurrentlyEnabled;
    }
    else if (name === 'gamepad') {
        if (isCurrentlyEnabled) {
            disableGamepadControll();
        }
        else {
            enableGamepadControll();
        }
    }
    else {
        console.warn(`Unknown option name`, event.target);
        return;
    }

    target.dataset.enabled = !isCurrentlyEnabled;
    target.classList.toggle('enabled');
    target.innerText = (!isCurrentlyEnabled ? 'Disable ' : 'Enable ') + name;
}


// === gamepad controll ===

var isGamepadLoopRunning = false;
var gamepadLoopIntervalId;

function enableGamepadControll() {
    // if gamepad is already connected
    if (navigator.getGamepads()[0]) {
        startGamepadLoop();
    }

    window.addEventListener("gamepadconnected", startGamepadLoop);
    window.addEventListener("gamepaddisconnected", stopGamepadLoop);
}

function disableGamepadControll() {
    window.removeEventListener("gamepadconnected", startGamepadLoop);
    window.removeEventListener("gamepaddisconnected", stopGamepadLoop);
    stopGamepadLoop();
}   

function startGamepadLoop() {
    console.log("Gamepad connected!");
    if (!isGamepadLoopRunning) {
        isGamepadLoopRunning = true;
        gamepadControllOptionButton.classList.add('active');
        gamepadLoopIntervalId = setInterval(handleGamepadInput, gamepadRefreshDelayMs);
    }
}

function stopGamepadLoop() {
    console.log("Gamepad disconnected!");
    if (isGamepadLoopRunning) {
        isGamepadLoopRunning = false;
        gamepadControllOptionButton.classList.remove('active');
        clearInterval(gamepadLoopIntervalId);
    }
}

function handleGamepadInput() {
    const gamepads = navigator.getGamepads();
    const gamepad = gamepads[0];

    if (gamepad) {
        // turning
        const leftJoystickX = gamepad.axes[0];
        const turningSpeed = Math.round(leftJoystickX * 255);

        horizontalSlider.value = turningSpeed;
        handleDrivingCommand(turningMotor, turningSpeed);

        // speeding
        const rightTriggerValue = gamepad.buttons[7].value;
        const leftTriggerValue = gamepad.buttons[6].value;

        const drivingForwardSpeed = Math.round(rightTriggerValue * 255);
        const drivingBackwardsSpeed = Math.round(leftTriggerValue * 255);

        if (drivingForwardSpeed > drivingBackwardsSpeed) {
            verticalSlider.value = drivingForwardSpeed;
            handleDrivingCommand(speedMotor, drivingForwardSpeed);
        }
        else {
            verticalSlider.value = drivingBackwardsSpeed * -1;
            handleDrivingCommand(speedMotor, drivingBackwardsSpeed * -1);
        }
    }
}

// === keyboard controll ===

var isUpPressed = false;
var isDownPressed = false;
var isLeftPressed = false;
var isRightPressed = false;

function enableKeyboardControll(name) {
    if (name === 'arrows') {
        ['keydown', 'keyup'].forEach(name => {
            document.addEventListener(name, onArrowsKeyboardEvent);
        });
    }
    else if (name === 'WSAD') {
        ['keydown', 'keyup'].forEach(name => {
            document.addEventListener(name, onWsadKeyboardEvent);
        });
    }
    else {
        console.log(`Unknown keyboard control option to enable: '${name}'`);
    }
}

function disableKeyboardControll(name) {
    if (name === 'arrows') {
        ['keydown', 'keyup'].forEach(name => {
            document.removeEventListener(name, onArrowsKeyboardEvent);
        });
    }
    else if (name === 'WSAD') {
        ['keydown', 'keyup'].forEach(name => {
            document.removeEventListener(name, onWsadKeyboardEvent);
        });
    }
    else {
        console.log(`Unknown keyboard control option to disable: '${name}'`);
    }
}

function onWsadKeyboardEvent(event) {
    const updateType = updateIsPressedFromEvent(event, 'w', 's', 'a', 'd');
    updateIsPressedVariablesFromEvent(updateType);
}

function onArrowsKeyboardEvent(event) {
    const updateType = updateIsPressedFromEvent(event, 'ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight');
    updateIsPressedVariablesFromEvent(updateType);
}

function updateIsPressedVariablesFromEvent(event, forward, backward, left, right) {
    const key = event.key;
    const isPressed = event.type == 'keydown';

    if (key == forward) {
        isUpPressed = isPressed;
        return 'driving';
    }
    else if (key == backward) {
        isDownPressed = isPressed;
        return 'driving';
    }
    else if (key == left) {
        isLeftPressed = isPressed;
        return 'turning';
    }
    else if (key == right) {
        isRightPressed = isPressed;
        return 'turning';
    }
}

function detectDrivingDirectionFromKeboard(updateType) {
    if (updateType === 'driving') {
        if (isUpPressed == isDownPressed) {
            handleDrivingCommand(speedMotor, 0);
            verticalSlider.value = 0;
        }
        else if (isUpPressed) {
            handleDrivingCommand(speedMotor, 255);
            verticalSlider.value = 255;
        }
        else if (isDownPressed) {
            handleDrivingCommand(speedMotor, -255);
            verticalSlider.value = -255;
        }
    }

    if (updateType == 'turning') {
        if (isLeftPressed == isRightPressed) {
            handleDrivingCommand(turningMotor, 0);
            horizontalSlider.value = 0;
        }
        else if (isRightPressed) {
            handleDrivingCommand(turningMotor, 255);
            horizontalSlider.value = 255;
        }
        else if (isLeftPressed) {
            handleDrivingCommand(turningMotor, -255);
            horizontalSlider.value = -255;
        }
    }
}


// === sliders controll ===


verticalSlider.addEventListener('input', () => {
    handleDrivingCommand(speedMotor, verticalSlider.value);
});

horizontalSlider.addEventListener('input', () => {
    handleDrivingCommand(turningMotor, horizontalSlider.value);
});


// === reseting sliders value after releasing ===

['mouseup', 'touchend'].forEach(evt => {
    verticalSlider.addEventListener(evt, () => {
        verticalSlider.value = 0;
        handleDrivingCommand(speedMotor, 0);
    });
    horizontalSlider.addEventListener(evt, () => {
        horizontalSlider.value = 0;
        handleDrivingCommand(turningMotor, 0);
    });
});


// === handling full screen mode ===

document.getElementById('fullscreen-button')
    .addEventListener('click', () => document.body.requestFullscreen());