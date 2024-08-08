const readLine = require("readline");

//region consts
const LOWER_CASE = "abcdefghijklmnopqrstuvwxyz";
const UPPER_CASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const NUMBERS = "0123456789";
const SPECIAL_CHARS = "!@#$%^&*()_+?[].";
const ALL_CHARS = LOWER_CASE + UPPER_CASE + NUMBERS + SPECIAL_CHARS;
//endregion

function askForLength() {
    return new Promise((resolve) => {
        const rl = readLine.createInterface({
            input: process.stdin,
            output: process.stdout
        });

        rl.question('Input a length: ', (answer) => {
            rl.close();
            resolve(answer);
        });
    });
}

function randomChar(str) {
    const randomIndex = Math.floor(Math.random() * str.length);
    return str[randomIndex];
}

function pwgen(length) {
    if (length < 4) { return; }
    if (length > 64) {
        console.log("Number too high. Defaulting to a max of 64.");
        length = 64;
    }

    let response = "";

    response += randomChar(LOWER_CASE);
    response += randomChar(UPPER_CASE);
    response += randomChar(NUMBERS);
    response += randomChar(SPECIAL_CHARS);

    for (let i = 4; i < length; i++) {
        response += randomChar(ALL_CHARS);
    }

    response = response.split('').sort(() => Math.random() - 0.5).join('');

    return response;
}

async function main() {
    let len;
    if (process.argv[2] !== undefined) {
        len = parseInt(process.argv[2]);
    } else {
        len = await askForLength();
    }

    while (isNaN(len) || (len < 4)) {
        console.log("Invalid input. Enter a number greater than 3.")
        len = await askForLength();
    }

    const psswrd = pwgen(len);
    console.log("Generated password: " + psswrd);
}

main();
