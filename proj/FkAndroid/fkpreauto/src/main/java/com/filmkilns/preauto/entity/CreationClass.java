package com.filmkilns.preauto.entity;

import com.sun.tools.javac.code.Flags;
import com.sun.tools.javac.code.Symbol;

import java.util.ArrayList;
import java.util.List;

public class CreationClass {
    public static class Type {
        public Class<?> javaType;
        public String jniType;
        public String sig;
        public String cType;
    }

    public String name;
    public String path;
    public final List<CreationMethod> methods = new ArrayList<>();

    public CreationClass(Symbol.ClassSymbol symbol, String path) {
        this.name = getSimpleClassName(symbol);
        this.path = path;
        for (Symbol s : symbol.members().getSymbols()) {
            if (s instanceof Symbol.MethodSymbol && isNativeMethod((Symbol.MethodSymbol) s)) {
                this.methods.add(new CreationMethod((Symbol.MethodSymbol) s));
            }
        }
    }

    private String getSimpleClassName(Symbol.ClassSymbol symbol) {
        String name = symbol.className();
        return name.substring(name.lastIndexOf(".") + 1);
    }

    private boolean isNativeMethod(Symbol.MethodSymbol symbol) {
        return (symbol.flags() & Flags.NATIVE) != 0;
    }

    @Override
    public String toString() {
        return "CreationClass{" +
                "name='" + name + '\'' +
                ", path='" + path + '\'' +
                ", methods=" + methods +
                '}';
    }

    public static Class<?> getClassFromType(com.sun.tools.javac.code.Type type) {
        String className = type.toString().replaceAll("<.*>", "");
        try {
            if (className.equals("boolean")) {
                return boolean.class;
            } else if (className.equals("byte")) {
                return byte.class;
            } else if (className.equals("char")) {
                return char.class;
            } else if (className.equals("short")) {
                return short.class;
            } else if (className.equals("int")) {
                return int.class;
            } else if (className.equals("long")) {
                return long.class;
            } else if (className.equals("float")) {
                return float.class;
            } else if (className.equals("double")) {
                return double.class;
            } else if (className.equals("void")) {
                return void.class;
            } else if (className.equals("byte[]")) {
                return byte[].class;
            }
            return Class.forName(className);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            return Object.class;
        }
    }
}
