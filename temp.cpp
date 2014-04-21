                queue<int> Q;
                int h = src;
                Q.push(h);
                level[h] = 0;
                M[S.first][S.second] = '.';
                //till all the connected components are not searched or E is not found
                while(!Q.empty()){
                    pi s = seed[Q.front()];
                    Q.pop();
                    // h is the component at present
                    int h = nval[s.first][s.second];
                    cout<<"h = "<<h<<endl;
                    if(dest == h) return level[h];
                    queue<pi> q;
                    q.push(s);
                    while(!q.empty()){
                        pi p = q.front();
                        q.pop();
                        int x = p.first, y = p.second;
                        cout<<"x = "<<x<<" y = "<<y<<endl;
                    // if blank is found push all the four neighbours
                        if(0 <= x && x < n && 0 <= y && y < n && M[x][y] != 'F' && M[x][y] != 'x'){
                            print(M);
                            if(M[x][y] == '.'){
                                q.push(make_pair(x+1, y));
                                q.push(make_pair(x-1, y));
                                q.push(make_pair(x, y+1));
                                q.push(make_pair(x, y-1));
                            }
                            else if(M[x][y] == '|'){
                                if(0 <= x && x < n && 0 <= y-1 && y-1 < m && M[x][y-1] == '.' && level[nval[x][y-1]] == -1){
                                    level[nval[x][y-1]] = level[h] + 1;
                                    Q.push(nval[x][y-1]);
                                    cout<<"crossed from "<<x<<" "<<y<<" to "<<x<<" "<<y-1<<endl;
                                }
                                else if(0 <= x && x < n && 0 <= y+1 && y+1 < m && M[x][y+1] == '.' && level[nval[x][y+1]] == -1){
                                    level[nval[x][y+1]] = level[h] + 1;
                                    Q.push(nval[x][y+1]);
                                    cout<<"crossed from "<<x<<" "<<y<<" to "<<x<<" "<<y+1<<endl;
                                }
                                else if(0 <= x && x < n && 0 <= y-1 && y-1 < m && M[x][y-1] == '|')
                                    q.push(make_pair(x, y-1));
                                else if(0 <= x && x < n && 0 <= y+1 && y+1 < m && M[x][y+1] == '|')
                                    q.push(make_pair(x, y+1));
                            }
                            else if(M[x][y] == '-'){
                                if(0 <= x-1 && x-1 < n && 0 <= y && y < m && M[x-1][y] == '.' && level[nval[x-1][y]] == -1){
                                    level[nval[x-1][y]] = level[h] + 1;
                                    Q.push(nval[x-1][y]);
                                    cout<<"crossed from "<<x<<" "<<y<<" to "<<x-1<<" "<<y<<endl;
                                }
                                else if(0 <= x+1 && x+1 < n && 0 <= y && y < m && M[x+1][y] == '.' && level[nval[x+1][y]] == -1){
                                    level[nval[x+1][y]] = level[h] + 1;
                                    Q.push(nval[x+1][y]);
                                    cout<<"crossed from "<<x<<" "<<y<<" to "<<x+1<<" "<<y<<endl;
                                }
                                else if(0 <= x-1 && x-1 < n && 0 <= y && y < m && M[x-1][y] == '-')
                                    q.push(make_pair(x-1, y));
                                else if(0 <= x+1 && x+1 < n && 0 <= y && y < m && M[x+1][y] == '-')
                                    q.push(make_pair(x+1, y));
                            }
                            M[x][y] = 'x';
                        }//checking for x y at inner queue
                    }//end q
                }//end Q

