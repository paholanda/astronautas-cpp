#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Astronauta {
private:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

public:
    Astronauta(string cpf, string nome, int idade) {
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        this->vivo = true;
        this->disponivel = true;
    }

    string getCpf() const { return cpf; }
    string getNome() const { return nome; }
    int getIdade() const { return idade; }
    bool estaVivo() const { return vivo; }
    bool estaDisponivel() const { return disponivel; }

    void embarcar() { disponivel = false; }
    void desembarcar() { if (vivo) disponivel = true; }
    void morrer() { vivo = false; disponivel = false; }
};

class Voo {
private:
    int codigo;
    string estado;
    vector<string> cpfs;

public:
    Voo(int codigo) {
        this->codigo = codigo;
        this->estado = "planejado";
    }

    int getCodigo() const { return codigo; }
    string getEstado() const { return estado; }
    int getQuantidadeAstronautas() const { return cpfs.size(); }
    string getCpf(int posicao) const { return cpfs[posicao]; }
    bool temAstronautas() const { return !cpfs.empty(); }

    bool temAstronauta(string cpf) const {
        for (size_t i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) return true;
        }
        return false;
    }

    void adicionarAstronauta(string cpf) { cpfs.push_back(cpf); }

    bool removerAstronauta(string cpf) {
        for (size_t i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) {
                cpfs.erase(cpfs.begin() + i);
                return true;
            }
        }
        return false;
    }

    void lancar() { estado = "em curso"; }
    void explodir() { estado = "finalizado com explosao"; }
    void finalizar() { estado = "finalizado com sucesso"; }
};

class Agencia {
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    int buscarAstronauta(string cpf) {
        for (size_t i = 0; i < astronautas.size(); i++) {
            if (astronautas[i].getCpf() == cpf) return i;
        }
        return -1;
    }

    int buscarVoo(int codigo) {
        for (size_t i = 0; i < voos.size(); i++) {
            if (voos[i].getCodigo() == codigo) return i;
        }
        return -1;
    }

public:
    void cadastrarAstronauta(string cpf, string nome, int idade) {
        if (buscarAstronauta(cpf) != -1) {
            cout << "ERRO: astronauta com CPF " << cpf << " ja cadastrado" << endl;
            return;
        }
        astronautas.push_back(Astronauta(cpf, nome, idade));
        cout << "OK: astronauta " << cpf << " cadastrado" << endl;
    }

    void cadastrarVoo(int codigo) {
        if (buscarVoo(codigo) != -1) {
            cout << "ERRO: voo " << codigo << " ja cadastrado" << endl;
            return;
        }
        voos.push_back(Voo(codigo));
        cout << "OK: voo " << codigo << " cadastrado" << endl;
    }

    void adicionarAstronauta(string cpf, int codigo) {
        int idxAst = buscarAstronauta(cpf);
        if (idxAst == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        int idxVoo = buscarVoo(codigo);
        if (idxVoo == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[idxVoo].getEstado() != "planejado") {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (!astronautas[idxAst].estaVivo()) {
            cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
            return;
        }
        if (voos[idxVoo].temAstronauta(cpf)) {
            cout << "ERRO: astronauta " << cpf << " ja esta no voo " << codigo << endl;
            return;
        }
        voos[idxVoo].adicionarAstronauta(cpf);
        cout << "OK: astronauta " << cpf << " adicionado ao voo " << codigo << endl;
    }

    void removerAstronauta(string cpf, int codigo) {
        int idxAst = buscarAstronauta(cpf);
        if (idxAst == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        int idxVoo = buscarVoo(codigo);
        if (idxVoo == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[idxVoo].getEstado() != "planejado") {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (!voos[idxVoo].temAstronauta(cpf)) {
            cout << "ERRO: astronauta " << cpf << " nao esta no voo " << codigo << endl;
            return;
        }
        voos[idxVoo].removerAstronauta(cpf);
        cout << "OK: astronauta " << cpf << " removido do voo " << codigo << endl;
    }

    void lancarVoo(int codigo) {
        int idxVoo = buscarVoo(codigo);
        if (idxVoo == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[idxVoo].getEstado() != "planejado") {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (!voos[idxVoo].temAstronautas()) {
            cout << "ERRO: voo " << codigo << " nao possui astronautas" << endl;
            return;
        }

        for (int i = 0; i < voos[idxVoo].getQuantidadeAstronautas(); i++) {
            string cpf = voos[idxVoo].getCpf(i);
            int idxAst = buscarAstronauta(cpf);
            if (!astronautas[idxAst].estaVivo()) {
                cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
                return;
            }
            if (!astronautas[idxAst].estaDisponivel()) {
                cout << "ERRO: astronauta " << cpf << " esta indisponivel" << endl;
                return;
            }
        }

        voos[idxVoo].lancar();
        for (int i = 0; i < voos[idxVoo].getQuantidadeAstronautas(); i++) {
            string cpf = voos[idxVoo].getCpf(i);
            int idxAst = buscarAstronauta(cpf);
            astronautas[idxAst].embarcar();
        }
        cout << "OK: voo " << codigo << " lancado" << endl;
    }

    void explodirVoo(int codigo) {
        int idxVoo = buscarVoo(codigo);
        if (idxVoo == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[idxVoo].getEstado() != "em curso") {
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }
        voos[idxVoo].explodir();
        for (int i = 0; i < voos[idxVoo].getQuantidadeAstronautas(); i++) {
            string cpf = voos[idxVoo].getCpf(i);
            int idxAst = buscarAstronauta(cpf);
            astronautas[idxAst].morrer();
        }
        cout << "OK: voo " << codigo << " explodiu" << endl;
    }

    void finalizarVoo(int codigo) {
        int idxVoo = buscarVoo(codigo);
        if (idxVoo == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if (voos[idxVoo].getEstado() != "em curso") {
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }
        voos[idxVoo].finalizar();
        for (int i = 0; i < voos[idxVoo].getQuantidadeAstronautas(); i++) {
            string cpf = voos[idxVoo].getCpf(i);
            int idxAst = buscarAstronauta(cpf);
            astronautas[idxAst].desembarcar();
        }
        cout << "OK: voo " << codigo << " finalizado com sucesso" << endl;
    }

    void listarVoos() {
        cout << "LISTA DE VOOS" << endl;
        string estados[4] = {"planejado", "em curso", "finalizado com sucesso", "finalizado com explosao"};
        string titulos[4] = {"== planejado ==", "== em curso ==", "== finalizado com sucesso ==", "== finalizado com explosao =="};

        for (int e = 0; e < 4; e++) {
            cout << titulos[e] << endl;
            bool encontrou = false;
            for (size_t i = 0; i < voos.size(); i++) {
                if (voos[i].getEstado() == estados[e]) {
                    encontrou = true;
                    cout << "Voo " << voos[i].getCodigo() << ": ";
                    if (!voos[i].temAstronautas()) {
                        cout << "sem astronautas";
                    } else {
                        for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                            string cpf = voos[i].getCpf(j);
                            int idxAst = buscarAstronauta(cpf);
                            cout << cpf << " " << astronautas[idxAst].getNome();
                            if (j < voos[i].getQuantidadeAstronautas() - 1) cout << ", ";
                        }
                    }
                    cout << endl;
                }
            }
            if (!encontrou) cout << "(nenhum)" << endl;
        }
    }

    void listarMortos() {
        cout << "ASTRONAUTAS MORTOS" << endl;
        bool temMortos = false;
        for (size_t i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) {
                temMortos = true;
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome() << " voos:";
                for (size_t v = 0; v < voos.size(); v++) {
                    if (voos[v].getEstado() != "planejado" && voos[v].temAstronauta(astronautas[i].getCpf())) {
                        cout << " " << voos[v].getCodigo();
                    }
                }
                cout << endl;
            }
        }
        if (!temMortos) cout << "(nenhum)" << endl;
    }

    // Parte 2: Histórico do Astronauta e Relatórios Avançados
    void historicoAstronauta(string cpf) {
        int idxAst = buscarAstronauta(cpf);
        if (idxAst == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        cout << "HISTORICO DE ASTRONAUTA: " << astronautas[idxAst].getCpf() << " " << astronautas[idxAst].getNome() << endl;
        bool participou = false;
        for (size_t i = 0; i < voos.size(); i++) {
            if (voos[i].temAstronauta(cpf)) {
                participou = true;
                cout << "Voo " << voos[i].getCodigo() << " - " << voos[i].getEstado() << endl;
            }
        }
        if (!participou) {
            cout << "(nenhum voo)" << endl;
        }
    }

    void relatorioGeral() {
        cout << "RELATORIO DA AGENCIA" << endl;
        cout << "Total de astronautas: " << astronautas.size() << endl;
        cout << "Total de voos: " << voos.size() << endl;
    }
};

int main() {
    Agencia agencia;
    string comando;

    while (cin >> comando && comando != "FIM") {
        if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);
            agencia.cadastrarAstronauta(cpf, nome, idade);
        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.cadastrarVoo(codigo);
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.adicionarAstronauta(cpf, codigo);
        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.removerAstronauta(cpf, codigo);
        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.lancarVoo(codigo);
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.explodirVoo(codigo);
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.finalizarVoo(codigo);
        } else if (comando == "LISTAR_VOOS") {
            agencia.listarVoos();
        } else if (comando == "LISTAR_MORTOS") {
            agencia.listarMortos();
        } else if (comando == "HISTORICO_ASTRONAUTA") {
            string cpf;
            cin >> cpf;
            agencia.historicoAstronauta(cpf);
        } else if (comando == "RELATORIO_GERAL") {
            agencia.relatorioGeral();
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }
    return 0;
}
