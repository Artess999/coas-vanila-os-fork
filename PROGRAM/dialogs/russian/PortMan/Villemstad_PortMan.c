// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> квест №5 голл.линейки, забрать три флейта.
            if (pchar.questTemp.State == "ThreeFleutes_toPortMan")
            {
    			link.l1 = "Я к вам по поручению Стэвезанта. Мне необходимо принять командование над тремя флейтами.";
    			link.l1.go = "Step_H5_1";
            }
		break;

//************************************* Диалоги по голл.линейке *******************************
		case "Step_H5_1":
    		if (GetCompanionQuantity(pchar) == 1)
            {
                dialog.text = "Пожалуйста, принимайте. Три флейта поступают в ваше распоряжение.";
    			link.l1 = "Великолепно.";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("HL5_portManGiveFleuts");
            }
            else
            {
                dialog.text = "Да, я в курсе данного вопроса. Однако, чтобы принять командование над флейтами вам необходимо изабавиться от вашей эскадры. Прошу вас сделать это и затем вновь обратиться ко мне.";
    			link.l1 = "Хорошо, я так и сделаю.";
    			link.l1.go = "exit";
            }
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

