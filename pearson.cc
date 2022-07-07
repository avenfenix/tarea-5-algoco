#include <iostream>
#include <vector>


std::vector<unsigned int> greedy(unsigned int , std::vector<unsigned int> );
std::vector<unsigned int> pearson(std::vector<unsigned int> );
unsigned int productopunto(std::vector<unsigned int>, std::vector<unsigned int>);
void show_M(std::vector<unsigned int>, std::vector<unsigned int>);

int main(void){
    std::vector<unsigned int> d, vo;
    int n; /* Number of denominations */

	for(;;) {
		if(!(std::cin >> n))
			break;
		d.resize(n);
		for(int k = 0; k < n; k++)
			std::cin >> d[k];
        vo = pearson(d);
        if (vo.empty()){
            std::cout << "Greedy is optimal" << std::endl;
        } else{
            show_M(vo, d);
        }
    }

}


std::vector<unsigned int> greedy(unsigned int m, std::vector<unsigned int> d)
{
	std::vector<unsigned int> v(d.size(), 0);
	
	for (int i = 0 ; i < d.size()  ;i++){ 
		if (d[i] <= m && m > 0){
			v[i] = (int ) m / d[i]; 
			m = (int ) m % d[i]; 
		}
	}
	return v; 
}

std::vector<unsigned int> pearson(std::vector<unsigned int> d)
{
	// En los comentarios uso "c" como el set de denominaciones, lo hago asi para seguir el paper, aunque en mi codigo es el std::vector "d"
	std::vector<unsigned int> u(d.size(), 1);
        for (int i = 1; i < d.size(); i++){ 
            unsigned int p = d[i-1] - 1; // Calcula c[i−1] − 1 del teorema 1

            if (d[d.size()-3] <= p && p < d[0]+d[1]){ // Filtra los candidatos a contraejemplos minimos se encuentran en c[n-2] <= w < c[0] + c[1]
                std::vector<unsigned int> g = greedy(p, d); // Calcula G(c[i−1] − 1)
                for (int j = i; j < d.size(); j++){ 
                    std::vector<unsigned int> m(d.size(), 0);

                    for (int k = 0; k <= j-1; k++){ // Usando el teorema 1
                        m[k] = g[k];
                    }
                    m[j] = g[j] + 1;

                    
                    unsigned int w = productopunto(m, d); // Cantidad w representada por M(·)
                    unsigned int q_m = productopunto(m, u); // |M(w)|
                    std::vector<unsigned int> gw = greedy(w, d); // G(w)
                    unsigned int q_g = productopunto(gw, u); // |G(w)|
                    if (q_m < q_g){ // |M(w)| < |G(w)| => Greedy no es optimo
                        return m;
                    }
                }
                
            }
        }
        std::vector<unsigned int> v;
        return v;
}

unsigned int productopunto(std::vector<unsigned int>v1, std::vector<unsigned int>v2){
    unsigned int r = 0;
    for (int i = 0; i < v1.size(); i++){
        r+= v1[i]*v2[i];
    }
    return r;
}


void show_M(std::vector<unsigned int> v, std::vector<unsigned int> d){
    unsigned int c = productopunto(v, d);
    std::cout << "M(" << c << ") = ";
    std::cout << "[";
    for (int i = 0; i < v.size() - 1; i++){
        std::cout << v[i] << ", ";
    }
    std::cout << v[v.size()-1] << "]" << std::endl;
}



