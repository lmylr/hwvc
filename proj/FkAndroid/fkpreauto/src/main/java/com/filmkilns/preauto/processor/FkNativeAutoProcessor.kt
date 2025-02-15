package com.filmkilns.preauto.processor

import com.filmkilns.annotation.FkNativeAuto
import com.google.auto.service.AutoService
import java.io.File
import java.util.HashSet
import javax.annotation.processing.AbstractProcessor
import javax.annotation.processing.Messager
import javax.annotation.processing.ProcessingEnvironment
import javax.annotation.processing.RoundEnvironment
import javax.annotation.processing.SupportedSourceVersion
import javax.lang.model.SourceVersion
import javax.lang.model.element.ElementKind
import javax.lang.model.element.TypeElement
import javax.tools.Diagnostic

@AutoService(Process::class)
@SupportedSourceVersion(SourceVersion.RELEASE_8)
class FkNativeAutoProcessor : AbstractProcessor() {
    companion object {
        const val TAG = "FkNativeAutoProcessor"
    }
    private var messager: Messager? = null

    override fun init(processingEnvironment: ProcessingEnvironment) {
        super.init(processingEnvironment)
        messager = processingEnvironment.messager
        val file = File("/Volumes/FXS790_HD/Documents/Projects/AndroidStudioProjects/FilmKilns/proj/fk_flutter/test.txt")
        if (!file.exists()) {
            file.createNewFile()
        }
    }

    override fun process(set: Set<TypeElement?>?, roundEnvironment: RoundEnvironment): Boolean {
        try {
            val elements = roundEnvironment.getElementsAnnotatedWith(FkNativeAuto::class.java).filter { it.kind == ElementKind.CLASS }
            elements.forEach {
                logI(TAG, it.simpleName.toString())
            }
            val file = File("/Volumes/FXS790_HD/Documents/Projects/AndroidStudioProjects/FilmKilns/proj/fk_flutter/test.txt")
            if (!file.exists()) {
                file.createNewFile()
            }
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return true
    }

    override fun getSupportedAnnotationTypes(): Set<String> {
        val sets = HashSet<String>()
        sets.add(FkNativeAuto::class.java.canonicalName)
        return sets
    }

    protected fun logI(tag: String, msg: String?) {
        messager!!.printMessage(Diagnostic.Kind.NOTE, "$tag: $msg")
    }

    protected fun logE(tag: String, msg: String?) {
        messager!!.printMessage(Diagnostic.Kind.ERROR, "$tag: $msg")
    }
}