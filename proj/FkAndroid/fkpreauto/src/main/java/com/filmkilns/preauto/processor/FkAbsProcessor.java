package com.filmkilns.preauto.processor;

import java.util.Set;

import javax.annotation.processing.AbstractProcessor;
import javax.annotation.processing.Filer;
import javax.annotation.processing.Messager;
import javax.annotation.processing.ProcessingEnvironment;
import javax.annotation.processing.RoundEnvironment;
import javax.lang.model.SourceVersion;
import javax.lang.model.element.TypeElement;
import javax.tools.Diagnostic;

public abstract class FkAbsProcessor extends AbstractProcessor {
    private Messager messager;
    private Filer filer;
    private String projectDir, sourceMainDir;

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
        projectDir = processingEnvironment.getOptions().getOrDefault("projectDir", ".");
        sourceMainDir = processingEnvironment.getOptions().getOrDefault("sourceMainDir", ".");
        messager = processingEnvironment.getMessager();
//        filer = processingEnvironment.getFiler();
    }

    public Filer getFiler() {
        return filer;
    }

    public String getProjectDir() {
        return projectDir;
    }

    public String getSourceMainDir() {
        return sourceMainDir;
    }

    protected void logI(String tag, String msg) {
        messager.printMessage(Diagnostic.Kind.NOTE, tag +": " + msg);
    }

    protected void logE(String tag, String msg) {
        messager.printMessage(Diagnostic.Kind.ERROR, tag +": " + msg);
    }
}
