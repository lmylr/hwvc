package com.filmkilns.preauto.entity;

import com.sun.tools.javac.code.Symbol;

import java.util.ArrayList;
import java.util.List;

public class CreationMethod {
    public String name;
    public Class<?> returnType;
    public final List<CreationArg> args = new ArrayList<>();

    public CreationMethod(Symbol.MethodSymbol symbol) {
        this.name = symbol.getSimpleName().toString();
        this.returnType = CreationClass.getClassFromType(symbol.getReturnType());
        for (Symbol.VarSymbol s : symbol.params) {
            this.args.add(new CreationArg(s));
        }
    }

    @Override
    public String toString() {
        return "CreationMethod{" +
                "name='" + name + '\'' +
                ", returnType=" + returnType +
                ", args=" + args +
                '}';
    }
}
