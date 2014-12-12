/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.android.ide.eclipse.adt.internal.wizards.templates;

import java.util.List;
import java.util.Map;

import freemarker.template.TemplateBooleanModel;
import freemarker.template.TemplateMethodModelEx;
import freemarker.template.TemplateModel;
import freemarker.template.TemplateModelException;

/**
 * Method invoked by FreeMarker to check whether a given dependency is available
 * in this module
 */
public class FmHasDependencyMethod implements TemplateMethodModelEx {
    private final Map<String, Object> myParamMap;

    public FmHasDependencyMethod(Map<String, Object> paramMap) {
        myParamMap = paramMap;
    }

    @Override
    public TemplateModel exec(List args) throws TemplateModelException {
        if (args.size() != 1) {
            throw new TemplateModelException("Wrong arguments");
        }

        // TODO: Try to figure out if the project has appcompat etc
        // com.android.support:appcompat-v7

        // Not yet implemented
        return TemplateBooleanModel.FALSE;
    }
}