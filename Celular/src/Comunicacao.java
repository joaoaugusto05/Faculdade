public class Comunicacao {
    boolean internet;
    boolean sinal;
    boolean chip;
    Comunicacao(){
        internet = false;
        sinal = false;
        chip = false;
    }

    public boolean use_internet(){
        return internet;
    }
    public boolean use_sinal(){
        return sinal;
    }

    public void conect_internet(){
        System.out.println("Internet conectada!");
        internet = true;
    }
    public void conect_sinal(){
        System.out.println("Rede de Sinais Captada!");
        sinal = true;
    }

    public void conect_chip(){
        System.out.println("Chip conectado!");
        chip = true;
    }

    private boolean tem_chip(){
        return chip;
    }

    public void fazer_chamada(int numero){
        if(tem_chip() == true){
        System.out.println("Ligando para " + numero);
        }
        else{
            System.out.println("Não tem chip.");
        }
    }
    
}
