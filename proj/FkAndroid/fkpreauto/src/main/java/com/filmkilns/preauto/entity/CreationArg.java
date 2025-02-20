package com.filmkilns.preauto.entity;

import com.sun.tools.javac.code.Symbol;

public class CreationArg {
    public String name;
    public Class<?> type;

    public CreationArg(Symbol.VarSymbol symbol) {
        this.name = symbol.name.toString();
        this.type = CreationClass.getClassFromType(symbol.type);
    }

    @Override
    public String toString() {
        return "CreationArg{" +
                "name='" + name + '\'' +
                ", type=" + type.getSimpleName() +
                '}';
    }
}
