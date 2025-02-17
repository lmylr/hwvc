package com.filmkilns.preauto.processor;

import com.filmkilns.annotation.FkNativeAuto;
import com.google.auto.service.AutoService;

import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;
import org.apache.velocity.runtime.RuntimeConstants;
import org.apache.velocity.util.introspection.UberspectImpl;
import org.apache.velocity.util.introspection.UberspectPublicFields;

import java.io.File;
import java.io.IOException;
import java.io.Writer;
import java.util.HashSet;
import java.util.Set;

import javax.annotation.processing.ProcessingEnvironment;
import javax.annotation.processing.Processor;
import javax.annotation.processing.RoundEnvironment;
import javax.lang.model.element.TypeElement;
import javax.tools.JavaFileObject;

@AutoService(Processor.class)
public class FkNativeAutoProcessor extends FkAbsProcessor {
    private final static String TAG = "FkNativeAutoProcessor";

    @Override
    public synchronized void init(ProcessingEnvironment processingEnvironment) {
        super.init(processingEnvironment);
        logI(TAG, "init");
    }

    @Override
    public boolean process(Set<? extends TypeElement> set, RoundEnvironment env) {
        super.process(set, env);
        logI(TAG, "process");
        VelocityEngine ve = new VelocityEngine();
        ve.setProperty(RuntimeConstants.FILE_RESOURCE_LOADER_PATH, new File("/Volumes/FXS790_HD/Documents/Projects/AndroidStudioProjects/FilmKilns/proj/FkAndroid", "fkpreauto/src/main/resources/").getAbsolutePath());
        ve.setProperty(RuntimeConstants.UBERSPECT_CLASSNAME, UberspectImpl.class.getName() + ", " + UberspectPublicFields.class.getName());
        ve.init();;
        String classPackage = "com.alimin.fk.core";
        String $className = "FkSurfaceTextureSource3";
        Template t = ve.getTemplate("FkNativeInterface.mv");
        VelocityContext ctx = new VelocityContext();
        ctx.put("classPackage", classPackage);
        ctx.put("$className", $className);
        try {
            JavaFileObject source = getFiler().createSourceFile(classPackage + "." + $className);
            Writer writer = source.openWriter();
            t.merge(ctx, writer);
            writer.flush();
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return true;
    }

    @Override
    public Set<String> getSupportedAnnotationTypes() {
        Set<String> sets = new HashSet<>();
        sets.add(FkNativeAuto.class.getCanonicalName());
        return sets;
    }
}
