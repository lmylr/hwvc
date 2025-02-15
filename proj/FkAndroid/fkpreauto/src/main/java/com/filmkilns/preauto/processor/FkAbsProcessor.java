package com.filmkilns.preauto.processor;

import java.util.Set;

import javax.annotation.processing.AbstractProcessor;
import javax.annotation.processing.Messager;
import javax.annotation.processing.ProcessingEnvironment;
import javax.annotation.processing.RoundEnvironment;
import javax.lang.model.SourceVersion;
import javax.lang.model.element.TypeElement;
import javax.tools.Diagnostic;

public class FkAbsProcessor extends AbstractProcessor {
    private Messager messager;
    @Override
    public boolean process(Set<? extends TypeElement> set, RoundEnvironment env) {
        return false;
    }

    @Override
    public SourceVersion getSupportedSourceVersion() {
        return SourceVersion.latestSupported();
    }

    @Override
    public Set<String> getSupportedAnnotationTypes() {
        return super.getSupportedAnnotationTypes();
    }

    @Override
    public synchronized void init(ProcessingEnvironment processingEnvironment) {
        super.init(processingEnvironment);
        messager = processingEnvironment.getMessager();
    }

    protected void logI(String msg) {
        messager.printMessage(Diagnostic.Kind.NOTE, msg);
    }

    protected void logE(String msg) {
        messager.printMessage(Diagnostic.Kind.ERROR, msg);
    }
}
