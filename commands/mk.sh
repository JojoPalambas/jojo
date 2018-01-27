#!/bin/bash

cur='none'

for arg in $*; do
    if [ $cur = 'none' ]; then
        if [ $arg = '-aut' ]; then
            echo 'depott_g' > AUTHORS
        elif [ $arg = '-td' ]; then
            echo '[ ] Not done yet' >  TODO
            echo '[-] Being done' >> TODO
            echo '[+] Done but not debugged yet' >> TODO
            echo '[X] Done' >> TODO
            echo >> TODO
            echo '[ ] 1' >> TODO
            echo '    [ ] 1.1' >> TODO
            echo '    [ ] 1.2' >> TODO
            echo '    [ ] 1.3' >> TODO
            echo >> TODO
            echo '[ ] 2' >> TODO
            echo '    [ ] 2.1' >> TODO
            echo '    [ ] 2.2' >> TODO
            echo '    [ ] 2.3' >> TODO
            echo >> TODO
            echo '[ ] 3' >> TODO
            echo '    [ ] 3.1' >> TODO
            echo '    [ ] 3.2' >> TODO
            echo '    [ ] 3.3' >> TODO
        elif [ $arg = '-rm' ]; then
            echo '[Nothing done yet.]' > README
        elif [ $arg = '-cppclasshh' ]; then
            cur='cppclasshh'
        elif [ $arg = '-cppclasshxx' ]; then
            cur='cppclasshxx'
        elif [ $arg = '-cppmain' ]; then
            cur='cppmain'
        fi
    elif [ $cur = 'cppclasshh' ]; then
        echo '#pragma once' > "$arg.hh"
        echo >> "$arg.hh"
        echo '#include <>' >> "$arg.hh"
        echo '#include ""' >> "$arg.hh"
        echo >> "$arg.hh"
        echo "class $arg" >> "$arg.hh"
        echo '{' >> "$arg.hh"
        echo 'public:' >> "$arg.hh"
        echo "    $arg()" >> "$arg.hh"
        echo '      :' >> "$arg.hh"
        echo '    {}' >> "$arg.hh"
        echo >> "$arg.hh"
        echo "    ~$arg()" >> "$arg.hh"
        echo '    {}' >> "$arg.hh"
        echo >> "$arg.hh"
        echo 'protected:' >> "$arg.hh"
        echo >> "$arg.hh"
        echo 'private:' >> "$arg.hh"
        echo '};' >> "$arg.hh"
        echo >> "$arg.hh"
        echo "#include \"$arg.hxx\"" >> "$arg.hh"
        cur='none'
     elif [ $cur = 'cppclasshxx' ]; then
        echo '#pragma once' > "$arg.hxx"
        echo >> "$arg.hxx"
        echo "#include \"$arg.hh\"" >> "$arg.hxx"
        echo >> "$arg.hxx"
        echo "void $arg::func()" >> "$arg.hxx"
        echo '{' >> "$arg.hxx"
        echo '}' >> "$arg.hxx"
        cur='none'
     elif [ $cur = 'cppmain' ]; then
        echo "#include \"\"" >> "$arg.cc"
        echo >> "$arg.cc"
        echo "int main()" >> "$arg.cc"
        echo '{' >> "$arg.cc"
        echo '}' >> "$arg.cc"
        cur='none'
    fi
done
