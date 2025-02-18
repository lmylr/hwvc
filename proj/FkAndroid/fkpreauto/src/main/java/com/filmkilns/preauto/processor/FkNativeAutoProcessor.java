package com.filmkilns.preauto.processor;

import com.filmkilns.annotation.FkNativeAuto;
import com.google.auto.service.AutoService;
import com.google.common.collect.ImmutableSet;

import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;
import org.apache.velocity.runtime.RuntimeConstants;
import org.apache.velocity.util.introspection.UberspectImpl;
import org.apache.velocity.util.introspection.UberspectPublicFields;

import java.io.File;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.annotation.processing.ProcessingEnvironment;
import javax.annotation.processing.Processor;
import javax.annotation.processing.RoundEnvironment;
import javax.lang.model.element.Element;
import javax.lang.model.element.ElementKind;
import javax.lang.model.element.TypeElement;
import com.sun.tools.javac.code.Symbol;
import com.sun.tools.javac.code.Type;

@AutoService(Processor.class)
public class FkNativeAutoProcessor extends FkAbsProcessor {
    private final static String TAG = "FkNativeAutoProcessor";

    private static class CreationItem {
        String name;
        String path;

        @Override
        public String toString() {
            return "CreationItem{" +
                    "path='" + path + '\'' +
                    '}';
        }
    }

    @Override
    public synchronized void init(ProcessingEnvironment processingEnvironment) {
        super.init(processingEnvironment);
        logI(TAG, "init: projectDir=" + getProjectDir() + ", mainDir=" + getSourceMainDir());
    }

    @Override
    public boolean process(Set<? extends TypeElement> set, RoundEnvironment env) {
        logI(TAG, "process");
        Set<? extends Element> elements = env.getElementsAnnotatedWith(FkNativeAuto.class);
        List<CreationItem> items = new ArrayList<>();
        for (Element e : elements) {
            if (e.getKind() == ElementKind.CLASS) {
                Symbol.ClassSymbol symbol = (Symbol.ClassSymbol) e;
                FkNativeAuto ann = symbol.getAnnotation(FkNativeAuto.class);
                CreationItem creation = new CreationItem();
                creation.name = symbol.className();
                creation.path = ann.path();
                items.add(creation);
            }
        }
        logI(TAG, "items: " + items);
//        VelocityEngine ve = new VelocityEngine();
//        ve.setProperty(RuntimeConstants.FILE_RESOURCE_LOADER_PATH, new File("/Volumes/FXS790_HD/Documents/Projects/AndroidStudioProjects/FilmKilns/proj/FkAndroid", "fkpreauto/src/main/resources/").getAbsolutePath());
//        ve.setProperty(RuntimeConstants.UBERSPECT_CLASSNAME, UberspectImpl.class.getName() + ", " + UberspectPublicFields.class.getName());
//        ve.init();;
//        String classPackage = "com.alimin.fk.core";
//        String $className = "FkSurfaceTextureSource3";
//        Template t = ve.getTemplate("FkNativeInterface.mv");
//        VelocityContext ctx = new VelocityContext();
//        ctx.put("classPackage", classPackage);
//        ctx.put("$className", $className);
//        try {
//            JavaFileObject source = getFiler().createSourceFile(classPackage + "." + $className);
//            Writer writer = source.openWriter();
//            t.merge(ctx, writer);
//            writer.flush();
//            writer.close();
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
        return false;
    }

    @Override
    public Set<String> getSupportedAnnotationTypes() {
        return ImmutableSet.of(FkNativeAuto.class.getCanonicalName());
    }
}
