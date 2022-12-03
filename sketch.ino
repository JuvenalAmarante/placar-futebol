#include <LiquidCrystal.h>

#define gol1 19
#define gol2 18
#define analisa1 5
#define analisa2 4
#define confirmaAnalise 2
#define cancelaAnalise 15

#define luzVerde 23
#define luzAmarela 22
#define luzVermelha 21

LiquidCrystal lcd(12, 14, 27, 26, 25, 33);

int placar1 = 0;

int placar2 = 0;

bool analisando = false;

int timeAnalisado = 0;

byte fonte[8][8] =
    {
        {B01111, B11111, B11111, B11111, B11111, B11111, B11111, B11111},
        {B11111, B11111, B11111, B00000, B00000, B00000, B00000, B00000},
        {B11110, B11111, B11111, B11111, B11111, B11111, B11111, B11111},
        {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B01111},
        {B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111},
        {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11110},
        {B11111, B11111, B11111, B00000, B00000, B00000, B11111, B11111},
        {B11111, B00000, B00000, B00000, B00000, B11111, B11111, B11111}};

void setup()
{
  for (byte i = 0; i < 8; i++)
  {
    lcd.createChar(i, fonte[i]);
  }

  pinMode(gol1, INPUT_PULLUP);
  pinMode(gol2, INPUT_PULLUP);
  pinMode(analisa1, INPUT_PULLUP);
  pinMode(analisa2, INPUT_PULLUP);
  pinMode(confirmaAnalise, INPUT_PULLUP);
  pinMode(cancelaAnalise, INPUT_PULLUP);

  pinMode(luzVerde, OUTPUT);
  pinMode(luzAmarela, OUTPUT);
  pinMode(luzVermelha, OUTPUT);

  lcd.begin(16, 2);

  Serial.begin(9600);

  exibePlacar();
}

void loop()
{
  // Leitura dos botões
  int botaoGol1 = digitalRead(gol1);
  int botaoGol2 = digitalRead(gol2);
  int botaoAnalisa1 = digitalRead(analisa1);
  int botaoAnalisa2 = digitalRead(analisa2);
  int botaoCancelaAnalise = digitalRead(cancelaAnalise);
  int botaoConfirmaAnalise = digitalRead(confirmaAnalise);

  // Validação caso esteja em analise de gol
  if (analisando)
  {
    digitalWrite(luzAmarela, HIGH);

    delay(500);

    digitalWrite(luzAmarela, LOW);

    delay(500);

    if (!botaoConfirmaAnalise)
    {
      golConfirmado();
    }
    else if (!botaoCancelaAnalise)
    {
      golCancelado();
    }
  }
  else
  {
    if (!botaoGol1)
    {
      gol(1);
    }
    else if (!botaoGol2)
    {
      gol(2);
    }
    else if (!botaoAnalisa1)
    {
      analisaGol(1);
    }
    else if (!botaoAnalisa2)
    {
      analisaGol(2);
    }
  }
}

void gol(int time)
{
  lcd.clear();

  if (time == 1 || time == 2)
  {
    digitalWrite(luzVerde, HIGH);

    lcd.setCursor(3, 0);

    lcd.print("GOOOLLLL!!");

    // Ajusta o placar
    if (time == 1)
    {
      placar1++;
    }
    else if (time == 2)
    {
      placar2++;
    }

    delay(1500);
  }

  exibePlacar();
}

void analisaGol(int time)
{
  if (time == 1 || time == 2)
  {
    int placarAtual = 0;

    if (time == 1)
    {
      placarAtual = placar1;
    }
    else if (time == 2)
    {
      placarAtual = placar2;
    }

    if (placarAtual > 0)
    {
      lcd.clear();

      lcd.print("Verificando Gol...");

      analisando = true;
      timeAnalisado = time;
    }
  }
}

void golConfirmado()
{
  lcd.clear();

  lcd.setCursor(1, 0);

  lcd.print("Gol Confirmado");

  lcd.setCursor(6, 1);

  lcd.print("*_*");

  digitalWrite(luzVerde, HIGH);

  analisando = false;

  delay(1500);

  exibePlacar();
}

void golCancelado()
{
  lcd.clear();

  lcd.setCursor(1, 0);

  lcd.print("Gol Cancelado");

  lcd.setCursor(6, 1);

  lcd.print(";-;");

  digitalWrite(luzVermelha, HIGH);

  analisando = false;

  if (timeAnalisado == 1)
  {
    placar1--;
  }
  else if (timeAnalisado == 2)
  {
    placar2--;
  }

  delay(1500);

  exibePlacar();
}

void exibePlacar()
{
  lcd.clear();

  digitalWrite(luzVerde, LOW);
  digitalWrite(luzAmarela, LOW);
  digitalWrite(luzVermelha, LOW);

  String placar = "";

  if (placar1 < 10)
  {
    placar = placar + "0" + String(placar1);
  }
  else
  {
    placar = placar + String(placar1);
  }

  placar = placar + "-";

  if (placar2 < 10)
  {
    placar = placar + "0" + String(placar2);
  }
  else
  {
    placar = placar + String(placar2);
  }

  for (byte x = 0; x < 5; x++)
  {
    digito(placar[x], (x * 3));
  }
}

void digito(char valor, byte coluna)
{
  switch (valor)
  {
  case '0':
    digitar0(coluna);
    break;

  case '1':
    digitar1(coluna);
    break;

  case '2':
    digitar2(coluna);
    break;

  case '3':
    digitar3(coluna);
    break;

  case '4':
    digitar4(coluna);
    break;

  case '5':
    digitar5(coluna);
    break;

  case '6':
    digitar6(coluna);
    break;

  case '7':
    digitar7(coluna);
    break;

  case '8':
    digitar8(coluna);
    break;

  case '9':
    digitar9(coluna);
    break;

  case '-':
    digitarDivisor(coluna);
    break;

  default:
    break;
  }
}

void digitar0(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write((byte)0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(coluna, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
}

void digitar1(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(coluna + 1, 1);
  lcd.write(5);
}

void digitar2(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(coluna, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(7);
}

void digitar3(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(coluna, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void digitar4(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(2);
  lcd.setCursor(coluna + 2, 1);
  lcd.write(5);
}

void digitar5(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write((byte)0);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(coluna, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void digitar6(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write((byte)0);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(coluna, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void digitar7(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(coluna + 1, 1);
  lcd.write((byte)0);
}

void digitar8(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write((byte)0);
  lcd.write((byte)6);
  lcd.write(2);
  lcd.setCursor(coluna, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void digitar9(byte coluna)
{
  lcd.setCursor(coluna, 0);
  lcd.write((byte)0);
  lcd.write((byte)6);
  lcd.write((byte)2);
  lcd.setCursor(coluna + 2, 1);
  lcd.write((byte)5);
}

void digitarDivisor(byte coluna)
{
  lcd.setCursor(coluna + 1, 0);
  lcd.write(4);
  lcd.setCursor(coluna + 1, 1);
  lcd.write(1);
}
