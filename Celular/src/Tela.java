import java.util.Scanner;

public class Tela {
    boolean ligada;
    Tela(){
        ligada = false;
    }
    
    private boolean Screen_on(){
        if(ligada == false){
            System.out.println("Tela desligada. Não é possível completar a ação");
            return false;
        }
        return true;
    }

    public String le(){
        if(Screen_on() == true){
        Scanner s = new Scanner(System.in);
        return s.nextLine();
        }
        else{
            return "erro";
        }
    }
    public void ligar_tela(){
        System.out.println("Ligando a tela!");
        ligada = true;
    }

    public void desligar_tela(){
        System.out.println("Ligando a tela!");
        ligada = false;
    }

    
}
