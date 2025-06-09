!
let estadoJogo = "introducao"; // Estados: introducao, plantando, cuidando, colhendo, final
let tempoUltimaRegagem = 0;
let plantas = [];
let mensagem = "";
let numeroDePlantas = 100; // Agora são 100 plantas de girassóis
let ySolo; // Posição do solo
let dia = true; // Definindo se é dia ou noite

function setup() {
  createCanvas(800, 400);
  ySolo = height - 50; // Definindo a altura do solo (linha do chão)
  
  // Criando várias plantas de girassóis
  for (let i = 0; i < numeroDePlantas; i++) {
    plantas.push(new PlantaGirassol(random(100, width - 100), ySolo));
  }
}

function draw() {
  if (estadoJogo !== "final") {
    atualizarCicloDiaNoite(); // Alternar entre dia e noite

    // Céu do ciclo
    if (dia) {
      background(135, 206, 235); // Céu durante o dia
      desenharSol();
    } else {
      background(20, 24, 50); // Céu durante a noite
      desenharEstrelas();
    }

    // Solo do campo
    fill(40, 180, 70);
    rect(0, ySolo, width, 50);
  } else {
    mudarCenarioFinal(); // Novo cenário ao final do jogo
  }

  if (estadoJogo === "introducao") {
    mostrarIntroducao();
  } else if (estadoJogo === "plantando") {
    for (let planta of plantas) {
      planta.regar();
      planta.crescer();
      planta.mostrar();
    }
    mostrarMensagem("Você plantou seus girassóis! Regue com cuidado.");
  } else if (estadoJogo === "cuidando") {
    for (let planta of plantas) {
      planta.crescer();
      planta.mostrar();
    }
    mostrarMensagem("Os girassóis estão crescendo! Continue cuidando deles.");
  } else if (estadoJogo === "colhendo") {
    for (let planta of plantas) {
      planta.mostrar();
    }
    mostrarMensagem("Os girassóis estão prontos para a colheita!");
  } else if (estadoJogo === "final") {
    for (let planta of plantas) {
      planta.mostrar();
    }
    mostrarMensagem(mensagem);
  }
}

function mousePressed() {
  if (estadoJogo === "introducao") {
    estadoJogo = "plantando";
  } else if (estadoJogo === "plantando" || estadoJogo === "cuidando") {
    if (millis() - tempoUltimaRegagem > 2000) { // Limita a quantidade de regas
      for (let planta of plantas) {
        planta.regar();
      }
      tempoUltimaRegagem = millis();
      if (checarCrescimento()) {
        estadoJogo = "colhendo"; // Se todas as plantas crescerem, pode colher
      }
    }
  } else if (estadoJogo === "colhendo") {
    estadoJogo = "final";
    mensagem = verificarColheita();
  }
}

// Função para verificar o crescimento das plantas
function checarCrescimento() {
  for (let planta of plantas) {
    if (planta.altura < 50) {
      return false;
    }
  }
  return true;
}

// Função para determinar a qualidade da colheita
function verificarColheita() {
  let colhidas = 0;
  for (let planta of plantas) {
    if (planta.altura >= 50) {
      colhidas++;
    }
  }

  if (colhidas === plantas.length) {
    return "Parabéns! Todas as suas plantas de girassóis cresceram bem e foram colhidas com sucesso!";
  } else if (colhidas >= plantas.length / 2) {
    return "Boa colheita! Mais da metade das suas plantas cresceram bem.";
  } else {
    return "Sua colheita não foi muito boa. Algumas plantas não cresceram o suficiente.";
  }
}

// Função para alternar entre o ciclo dia e noite
function atualizarCicloDiaNoite() {
  if (frameCount % 300 === 0) { // Altera a cada 5 segundos (300 frames)
    dia = !dia;
  }
}

// Função para desenhar o sol
function desenharSol() {
  fill(255, 204, 0);
  ellipse(width - 80, 80, 100, 100);
}

// Função para desenhar as estrelas
function desenharEstrelas() {
  fill(255, 255, 255, 150); // Cor das estrelas
  for (let i = 0; i < 100; i++) {
    let x = random(width);
    let y = random(height / 2); // Limita as estrelas a parte superior
    ellipse(x, y, random(1, 3), random(1, 3));
  }
}

// Função para exibir mensagens
function mostrarMensagem(msg) {
  fill(255);
  textSize(18);
  textAlign(CENTER);
  text(msg, width / 2, 30);
}

// Função para exibir a introdução
function mostrarIntroducao() {
  fill(255);
  textSize(18);
  textAlign(CENTER);
  text("Bem-vindo à sua fazenda de girassóis! Cultive suas plantas com cuidado.\nClique para plantar suas sementes!", width / 2, height / 2 - 40);
}

// Função para mudar o cenário final
function mudarCenarioFinal() {
  background(210); // Céu acinzentado de final
  fill(100);       // Solo de asfalto/cimento
  rect(0, ySolo, width, 50);
}

// Classe para a planta de girassol
class PlantaGirassol {
  constructor(x, y) {
    this.x = x;
    this.y = y;
    this.altura = 0;
    this.maxAltura = 100;
    this.velocidadeCrescimento = 0.2;
    this.necessitaAgua = true;
  }

  // Regar a planta
  regar() {
    if (this.altura < this.maxAltura) {
      this.necessitaAgua = false;
    }
  }

  // Crescer a planta
  crescer() {
    if (!this.necessitaAgua && this.altura < this.maxAltura) {
      this.altura += this.velocidadeCrescimento;
    } else {
      this.altura -= 0.1; // Diminui a altura se não for regada
    }
  }

  // Mostrar a planta de girassol
  mostrar() {
    // Desenhando o caule
    fill(34, 139, 34);
    rect(this.x - 5, this.y - this.altura, 10, this.altura); // Correção no cálculo de Y

    // Desenhando as folhas
    fill(34, 139, 34);
    ellipse(this.x - 15, this.y - this.altura + 30, 20, 20); // Folha esquerda
    ellipse(this.x + 15, this.y - this.altura + 30, 20, 20); // Folha direita

    // Desenhando a flor de girassol no topo da planta
    if (this.altura > 50) {
      fill(255, 215, 0); // Cor da flor
      ellipse(this.x, this.y - this.altura, 30, 30); // Flor do girassol
    }
  }
}
