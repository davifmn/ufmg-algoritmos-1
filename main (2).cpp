#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

class LigasMetalicas
{
private:
    int *ligas_metalicas;
    int qtd_tipos_ligas;

public:
    LigasMetalicas(int qtd_tipos_ligas)
    {
        this->qtd_tipos_ligas = qtd_tipos_ligas;

        this->ligas_metalicas = new int[this->qtd_tipos_ligas];

        for (int i = 0; i < this->qtd_tipos_ligas; i++)
        {
            // Tamanho disponivel para cada liga
            cin >> this->ligas_metalicas[i];
        }
    }

    int getMinLigas(int demanda)
    {
        int **cortes = new int *[this->qtd_tipos_ligas + 1];
        for (int i = 0; i < this->qtd_tipos_ligas + 1; ++i)
        {
            cortes[i] = new int[demanda + 1];
        }

        // Aqui, o valor inicial da primeira coluna da matriz que armazena a solução é definido como 0, já que quando precisamos de 0 barras para atender a uma demanda de 0.
        for (int i = 0; i <= this->qtd_tipos_ligas; i++)
        {
            for (int j = 0; j <= demanda; j++)
            {
                if (j == 0)
                    cortes[i][j] = 0;
                else
                    cortes[i][j] = INF;
            }
        }

        // Preenchendo a tabela usando a técnica de programação dinâmica.
        for (int i = 1; i <= this->qtd_tipos_ligas; i++)
        {
            for (int j = 1; j <= demanda; j++)
            {
                if (this->ligas_metalicas[i - 1] <= j)
                {
                    // Duas variaveis, para caso a liga seja adicionada ou não, pega o valor mininimo entre as duas para verificar
                    int addLiga = cortes[i][j - this->ligas_metalicas[i - 1]] + 1;
                    int excLiga = cortes[i - 1][j];
                    cortes[i][j] = min(addLiga, excLiga);
                }
                else
                    cortes[i][j] = cortes[i - 1][j];
            }
        }

        return cortes[this->qtd_tipos_ligas][demanda];
    }
};

int main(int argc, char const *argv[])
{
    // Quantidade de casos de teste
    int n_casos;
    cin >> n_casos;

    while (n_casos > 0)
    {
        // Quantidade de tipos de ligas e a demanda do cliente
        int qtd_tipos_ligas, demanda;
        cin >> qtd_tipos_ligas >> demanda;

        // Criar o objeto para gerenciar as ligas metalicas
        LigasMetalicas ligasMetalicas(qtd_tipos_ligas);

        // Resultado de quantidade minima de ligas
        int resultado = ligasMetalicas.getMinLigas(demanda);

        // Imprime o resultado da quantidade minima de ligas metalicas
        cout << resultado << endl;

        // Decrementa o contador
        n_casos--;
    }

    return 0;
}