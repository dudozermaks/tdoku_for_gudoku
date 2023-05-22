#include "../include/generator.hpp"

using namespace std;

int main(int argc, char **argv) {
    GeneratorOptions options{};

    ketopt_t opt = KETOPT_INIT;
    char c;
    while ((c = (char) ketopt(&opt, argc, argv, 1, "a::c:d:e:g:hl:m:n:p::r:s:u", nullptr)) != -1) {
        switch (c) {
            case 'c': {
                options.clue_weight = stod(opt.arg);
                break;
            }
            case 'g': {
                options.guess_weight = stod(opt.arg);
                break;
            }
            case 'r': {
                options.random_weight = stod(opt.arg);
                break;
            }
            case 'd': {
                options.clues_to_drop = stoi(opt.arg);
                break;
            }
            case 'e': {
                options.num_evals = stoi(opt.arg);
                break;
            }
            case 'l': {
                options.max_puzzles = stoll(opt.arg);
                break;
            }
            case 'm': {
                options.minimize = opt.arg == nullptr ? true : stoi(opt.arg) > 0;
                break;
            }
            case 'n': {
                options.num_puzzles_in_pool = stoi(opt.arg);
                break;
            }
            case 'a': {
                options.display_all = opt.arg == nullptr ? true : stoi(opt.arg) > 0;
                break;
            }
            case 'p': {
                options.pencilmark = opt.arg == nullptr ? true : stoi(opt.arg) > 0;
                break;
            }
            case 's': {
                options.solver = stoi(opt.arg);
                break;
            }
            case 'h':
            default: {
                cout << "usage: generate <options> <pattern_file>\n" << endl;
                cout << "options:\n" << endl;
                cout << "  -c <clue_weight>    scoring weight for number of clues\n";
                cout << "  -g <guess weight>   scoring weight(exponent) for geo mean guesses\n";
                cout << "  -r <random weight>  scoring weight for uniform noise\n";
                cout << "  -d <drop>           number of clues to drop before re-completing\n";
                cout << "  -e <num_evals>      number of permutations to eval for guess estimate\n";
                cout << "  -l <limit>          limit number of puzzles to generate\n";
                cout << "  -m [0|1]            minimize generated puzzles\n";
                cout << "  -n <pool size>      number of top scored puzzles to keep in pool\n";
                cout << "  -a [0|1]            display all puzzles (not just top scored)\n";
                cout << "  -p [0|1]            generate pencilmark puzzles\n";
                cout << "  -s [0|1|2]          solver for eval: 0=tdoku,1=minisat,2=gurobi\n";
                cout << "  -h                  display this help message\n";
                exit(0);
            }
        }
    }

    Generator generator(options);
    if (argc == opt.ind) {
        generator.InitEmpty();
    } else {
        generator.Load(argv[opt.ind]);
    }
    generator.Generate();
}

