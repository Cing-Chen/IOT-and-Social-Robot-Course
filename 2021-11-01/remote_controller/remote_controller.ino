/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 29 Jan 2019 06:28:05 GMT
 */

#include <LRemote.h>

LRemoteLabel label1;
LRemoteButton button_forward;
LRemoteButton button_backward;
LRemoteButton button_left;
LRemoteButton button_right;
LRemoteButton button_stop;

void setup()
{
  LRemote.setName("Hagua");
  LRemote.setOrientation(RC_PORTRAIT);
  LRemote.setGrid(3, 4);
    label1.setPos(0, 0);
    label1.setText("7697 Robot");
    label1.setSize(3, 1);
    label1.setColor(RC_ORANGE);
    LRemote.addControl(label1);

    button_forward.setPos(1, 1);
    button_forward.setText("^");
    button_forward.setSize(1, 1);
    button_forward.setColor(RC_BLUE);
    LRemote.addControl(button_forward);

    button_backward.setPos(1, 3);
    button_backward.setText("v");
    button_backward.setSize(1, 1);
    button_backward.setColor(RC_BLUE);
    LRemote.addControl(button_backward);

    button_left.setPos(0, 2);
    button_left.setText("<");
    button_left.setSize(1, 1);
    button_left.setColor(RC_BLUE);
    LRemote.addControl(button_left);

    button_right.setPos(2, 2);
    button_right.setText(">");
    button_right.setSize(1, 1);
    button_right.setColor(RC_BLUE);
    LRemote.addControl(button_right);

    button_stop.setPos(1, 2);
    button_stop.setText("o");
    button_stop.setSize(1, 1);
    button_stop.setColor(RC_YELLOW);
    LRemote.addControl(button_stop);
  LRemote.begin();
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}


void loop()
{
  LRemote.process();
  if (button_forward.isValueChanged()) {
    if (button_forward.getValue() == 1) {
      label1.updateText(String("Forward"));
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);

    } else {
      label1.updateText(String("STOP"));
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);

    }

  }
  if (button_backward.isValueChanged()) {
    if (button_backward.getValue() == 1) {
      label1.updateText(String("Backward"));
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);

    } else {
      label1.updateText(String("STOP"));
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);

    }

  }
  if (button_left.isValueChanged()) {
    if (button_left.getValue() == 1) {
      label1.updateText(String("LEFT"));
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);

    } else {
      label1.updateText(String("STOP"));
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);

    }

  }
  if (button_right.isValueChanged()) {
    if (button_right.getValue() == 1) {
      label1.updateText(String("RIGHT"));
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);

    } else {
      label1.updateText(String("STOP"));
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);

    }

  }
  if (button_stop.isValueChanged()) {
    if (button_stop.getValue() == 1) {
      label1.updateText(String("STOP"));
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);

    }

  }
  delay(100);
}