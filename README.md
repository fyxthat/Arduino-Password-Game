<h1 aligh='center'> Arduino Password Game </h1>

An Arduino-based reaction game where the player must enter a randomly generated 8-digit password using physical buttons, before a countdown timer expires.

Built with the [MultiFuncShield](https://www.multifunction-shield.com/) and the `TimerOne` library.

---

## ⚙️ How It Works

1. **Setup phase** — the player turns the potentiometer to set the round duration (mapped to 45–90 seconds) and presses **Button 1** to confirm.
2. A random 8-digit password is generated (each digit is 1, 2, or 3, matching the available buttons).
3. The countdown starts and the display shows the remaining time.
4. The player must press the buttons in the exact sequence of the hidden password.
5. **Correct press** → a short beep sounds and the binary LED counter advances.
6. **Wrong press** → 2 seconds are deducted from the timer and the progress resets.
7. **Last 10 seconds** → the display blinks and a warning beep sounds every second.

### 🏆 Win / Lose 😔

| Condition | Display | Sound |
|-----------|---------|-------|
| All 8 digits correct | `SAFE` | 3 beeps |
| Timer reaches 0 | `ICE` | continuous alarm (~5 min) |

---

## 🔧 Hardware Required

- Arduino Uno (or compatible board)
- [MultiFuncShield](https://www.multifunction-shield.com/) (4-digit 7-segment display, 3 buttons, 4 LEDs, buzzer, potentiometer)

---

## 📖 Libraries

| Library | Purpose |
|---------|---------|
| [`TimerOne`](https://github.com/PaulStoffregen/TimerOne) | Hardware timer used by MultiFuncShield |
| [`MultiFuncShield`](https://www.multifunction-shield.com/downloads.html) | Shield abstraction (display, buttons, LEDs, buzzer) |

Install both through the Arduino IDE Library Manager, if MultiFuncShield doesn't appear, install it manually.

---

## 💡 LED Binary Counter

The 4 on-board LEDs display the number of correct button presses in binary (0–8), giving the player real-time feedback of the password.

| Correct presses | LED 4 | LED 3 | LED 2 | LED 1 |
|:-:|:-:|:-:|:-:|:-:|
| 0 | ○ | ○ | ○ | ○ |
| 1 | ○ | ○ | ○ | ● |
| 2 | ○ | ○ | ● | ○ |
| … | … | … | … | … |
| 8 | ● | ○ | ○ | ○ |
