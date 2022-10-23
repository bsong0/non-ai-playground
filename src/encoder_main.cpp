#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;
int xx = 0, yy = 0, zz = -1; // change
struct Point
{
    double x, y, z;
}; // Spatial coordinates

struct Triangle
{
    int i, j, k;
}; // Vertex numbers for a triangle

//======================================================================


int get_vn_size(string filename) {
    int count = 0;
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        if (line.substr(0, 2) == "vn") {
            count ++;
        }
    }
    cout << "count vn = " << count << endl;
    return count;
}

void getFacesAndVertices(string filename, const char* output_location, vector<Point> &vertices, vector<Triangle> &faces)
{
    int vn_size = get_vn_size(filename);
    faces.clear();
    vertices.clear(); // comment out to add to an existing collection

    string line;
    string c;
    int i, j, k;
    double x, y, z;
    string si, sj, sk;

    ifstream in(filename);
    FILE *out = fopen(output_location, "w"); // Change
    bool flag_first = false;
    bool is_f_first = true;
    int count = 1;
    int no_use[84717];
    int first_of_deplicate = 0;
    int count_no_use = 0;
    while (getline(in, line)) // read whole line
    {
        if (line.find_first_of("vVfF") == string::npos)
            continue; // skip pointless lines

        istringstream ss(line); // put line into a stream for input
        ss >> c;                // get first character
        // switch (c)
        if (c == "v")
        {
            // case 'v':
            //  VERTICES
            //  case 'V':
            //      (either case)
            ss >> x >> y >> z; // read from internal stream

            if (x == xx && y == yy & z == zz && flag_first) // Change
            {
                // vertices.push_back({x, y, z}); // add to vector
                // don't write to the file
                no_use[count_no_use++] = count; // record no use
                count++;
                // break;
            }
            else
            {
                // write to the file
                fprintf(out, "v %f %f %f \n", x, y, z);

                if (x == xx && y == yy & z == zz) // Change
                {
                    flag_first = true;
                    first_of_deplicate = count;
                    //   break;
                }
                count++;
            }
        }
        else if (c == "f")
        {
            int update_vn[vn_size];
            if (is_f_first)
            {
                int current = 0;
                int p;
                bool flag_first_in = true;
                for (int m = 1; m <= vn_size-1; m++)
                {
                    for (p = 0; p < count_no_use; p++)
                    {
                        if (no_use[p] == m)
                        {
                            update_vn[m] = first_of_deplicate; // Change First Met
                            // if (flag_first_in)
                            // {
                            //     current++;
                            // }
                            current++;
                            flag_first_in = false;
                            break;
                        }
                    }
                    if (p == count_no_use)
                    {
                        update_vn[m] = m - current;
                    }
                }
                is_f_first = false;
            }

            // case 'f':                 // FACES
            //  case 'F':                 //    (either case)
            ss >> si >> sj >> sk; // FIRST, read into individual strings
            fprintf(out, "f ");
            // %d//%d %d \n", x, y, z);
            cout << si << endl;
            i = stoi(si);
            fprintf(out, "%d//", i);
            int count;
            count = si.find("//");
            count = count + 2;
            si = si.substr(count);
            i = stoi(si); // the second arg
            i = update_vn[i];
            fprintf(out, "%d ", i);

            j = stoi(sj);
            fprintf(out, "%d//", j);
            count = sj.find("//");
            count = count + 2;
            sj = sj.substr(count);
            j = stoi(sj);
            j = update_vn[j];
            fprintf(out, "%d ", j);

            k = stoi(sk);
            fprintf(out, "%d//", k);
            count = sk.find("//");
            count = count + 2;
            sk = sk.substr(count);
            k = stoi(sk);
            k = update_vn[k];
            fprintf(out, "%d\n", k);

            faces.push_back({i, j, k}); // add to vector
                                        // break;
        }
    }
    in.close();
    fclose(out);
}
//======================================================================vvvv


int main(int argc, char** argv)
{
    puts("");
    vector<Point> vertices;
    vector<Triangle> faces;
    string input_location;
    string output_location;
    // string filename = "2CylinderEngine.obj"; // Change

    for (int i = 0; i< argc; i++) {
        if (!strcmp(argv[i], "-i")) {
            input_location = argv[++i];
        }
        else if (!strcmp(argv[i], "-o")) {
            output_location = argv[++i];
        }
    }
    cout << input_location << ' ' << output_location;
     getFacesAndVertices(input_location, output_location.c_str(), vertices, faces);

    // cout << "Vertices:\n";
    // // for (Point p : vertices)
    // //     cout << p.x << "  " << p.y << "  " << p.z << '\n';

    // cout << "\n\n";

    // cout << "Triangles\n";

    // cout << faces[1].i << "  " << faces[1].j << "  " << faces[1].k << '\n';
    //  for (Triangle t : faces)
    //  cout << t.i << "  " << t.j << "  " << t.k << '\n';
}
