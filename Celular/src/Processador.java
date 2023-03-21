public class Processador {
    
    private int capacidade;
    private int utilizacao;

    private int clean(){
        if (utilizacao == capacidade){
            System.out.println("O sistema está superlotado... Fechando algumas aplicações.");
            utilizacao = 0;
        }

        return 0;
    }

    
    Processador(){
      capacidade =  5;
      utilizacao = 0;
    }
    

    public void add_use(){
        clean();
        utilizacao += 1;
    };

    public float memoria_usada(){
        return utilizacao * 100 /capacidade;
    }
}
